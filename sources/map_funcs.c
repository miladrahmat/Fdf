/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:37:46 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/18 16:50:32 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_size(int fd, char **arg)
{
	int		count;
	char	*gnl;

	count = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		count++;
		free(gnl);
		gnl = get_next_line(fd);
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
	map->point = malloc((size + 1) * sizeof(t_point *));
	if (map->point == NULL)
		return (-1);
	map->point_alloc = true;
	return (1);
}

int	read_map(t_map *map, int fd, char **arg)
{
	char	**split;
	char	*gnl;

	if (alloc_map(map, fd, arg) < 0)
		return (-1);
	map->height = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		map->x = 0;
		map->point[map->height] = malloc(ft_strlen(gnl) * sizeof(t_point));
		split = ft_split(gnl, ' ');
		free(gnl);
		if (split == NULL || *split == NULL || map->point[map->height] == NULL)
		{
			free_map(map);
			return (-1);
		}
		if (create_map(map, split) < 0)
			return (-1);
		split_free(split);
		gnl = get_next_line(fd);
	}
	return (1);
}

int	create_map(t_map *map, char **split)
{
	int		i;
	int		res;

	i = 0;
	while (split[i] != NULL)
	{
		if (ft_strchr(split[i], ',') != 0)
			get_color(map, split[i]);
		else
		{
			res = ft_atoi(split[i]);
			map->point[map->height][map->x].z = res;
			map->point[map->height][map->x].color = \
				ft_atoi_base("ffffffff", 16);
			convert_to_rgba(&map->point[map->height][map->x]);
		}
		map->x++;
		i++;
	}
	if (map->height == 0)
		map->width = map->x;
	if (map->x != map->width)
		return (-1);
	map->height++;
	return (1);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->point_alloc == true)
	{
		while (i < map->height)
		{
			free(map->point[i]);
			i++;
		}
	}
	free(map->point);
}
