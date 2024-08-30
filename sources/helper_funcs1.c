/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:37:57 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 16:12:32 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_backup(t_map *map, int err)
{
	int	i;

	if (err == 1)
		i = map->height;
	else
		i = map->height - 1;
	if (map->backup_alloc == true)
	{
		while (i > 0)
			free(map->backup[i--]);
		free(map->backup[i]);
		free(map->backup);
		map->backup_alloc = false;
	}
}

void	free_gnl(int fd)
{
	char	*gnl;

	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
}

void	inital_points(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->point[y][x].x = x;
			map->point[y][x].y = y;
			x++;
		}
		y++;
	}
}

int	get_backup(t_map *map)
{
	int	x;
	int	y;

	map->backup = malloc((map->height + 1) * sizeof(t_point *));
	if (map->backup == NULL)
		return (-1);
	map->backup_alloc = true;
	y = 0;
	while (y < map->height)
	{
		map->backup[y] = malloc((map->width + 1) * sizeof(t_point));
		if (map->backup[y] == NULL)
			return (-1);
		x = 0;
		while (x < map->width)
		{
			map->backup[y][x].z = map->point[y][x].z;
			x++;
		}
		y++;
	}
	return (1);
}

void	center_map(t_map *map)
{
	int		x;
	int		y;
	double	cx;
	double	cy;

	cx = map->point[map->height / 2][map->width / 2].x;
	cy = map->point[map->height / 2][map->width / 2].y;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->point[y][x].x -= cx;
			map->point[y][x].y -= cy;
			map->point[y][x].x += map->img->width / 2;
			map->point[y][x].y += map->img->height / 2;
			map->point[y][x].x += map->x_trans;
			map->point[y][x].y += map->y_trans;
			x++;
		}
		y++;
	}
}
