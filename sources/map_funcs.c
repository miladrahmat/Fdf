/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:37:46 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/15 14:11:49 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_size(int fd, char **arg)
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

static int	alloc_map(t_map *map, int fd, char **arg)
{
	int		size;

	size = get_size(fd, arg);
	if (size == -1 || size == 0)
		return (-1);
	map->memory = malloc((size + 1) * sizeof(int *));
	if (map->memory == NULL)
		return (-1);
	map->mem_alloc = true;
	return (1);
}

int	read_map(t_map *map, int fd, char **arg)
{
	char	**split;
	char	*gnl;

	if (alloc_map(map, fd, arg) < 0)
		return (-1);
	map->len_y = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		map->x = 0;
		map->memory[map->len_y] = malloc((ft_strlen(gnl) / 2 + 1) \
			* sizeof(int));
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
