/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:37:46 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/12 16:44:37 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(t_map *map, int fd, char **arg)
{
	char	**split;
	char	*gnl;
	int		size;

	size = get_size(fd, arg);
	if (size == -1 || size == 0)
		return (-1);
	map->memory = malloc((size + 1) * sizeof(int *));
	if (map->memory == NULL)
		return (-1);
	map->mem_alloc = true;
	map->len_y = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		map->x = 0;
		map->memory[map->len_y] = malloc(ft_strlen(gnl) * sizeof(int));
		split = ft_split(gnl, ' ');
		free(gnl);
		if (split == NULL || *split == NULL || map->memory[map->len_y] == NULL)
		{
			free_map(map);
			return (-1);
		}
		if (create_map(map, split) < 0)
			return (-1);
		gnl = get_next_line(fd);
	}
	return (1);
}

int	create_map(t_map *map, char **split)
{
	int	i;
	int	res;

	i = 0;
	while (split[i] != NULL)
	{
		res = ft_atoi(split[i]);
		ft_memcpy(&map->memory[map->len_y][map->x], &res, sizeof(res));
		map->x++;
		i++;
	}
	if (map->len_y == 0)
		map->len_x = map->x;
	if (map->x != map->len_x)
	{
		free_map(map);
		split_free(split);
		return (-1);
	}
	map->len_y++;
	split_free(split);
	return (1);
}

int	get_size(int fd, char **arg)
{
	char	buf;
	int		count;
	ssize_t	check;

	count = 0;
	buf = '0';
	check = 1;
	while (check > 0)
	{
		check = read(fd, &buf, sizeof(buf));
		if (check == -1)
			return (-1);
		if (buf == '\n' || buf == '\0')
			count++;
	}
	close(fd);
	fd = open(arg[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	else
		return (count);
}

void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr[i]);
	free(arr);
	arr = NULL;
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->mem_alloc == true)
	{
		while (i < map->len_y)
		{
			free(map->memory[i]);
			i++;
		}
		i = 0;
	}
	if (map->point_alloc == true)
	{
		while (i < map->len_y)
		{
			free(map->point[i]);
			i++;
		}
	}
	free(map->memory);
	map->len_x = 0;
	map->len_y = 0;
	map->x = 0;
	map->y = 0;
	map->z = 0;
}
