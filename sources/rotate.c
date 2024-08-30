/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:37:56 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 12:01:30 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z(int x, int y, t_map *map)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = map->point[y][x].x;
	tmp_y = map->point[y][x].y;
	map->point[y][x].x = tmp_x * cos(map->gamma) - tmp_y * sin(map->gamma);
	map->point[y][x].y = tmp_x * sin(map->gamma) + tmp_y * cos(map->gamma);
}

static void	rotate_y(int x, int y, t_map *map)
{
	double	tmp_x;

	tmp_x = map->point[y][x].x;
	map->point[y][x].x = tmp_x * cos(map->theta) + \
		map->point[y][x].z * sin(map->theta);
	map->point[y][x].z = map->point[y][x].z * \
		cos(map->theta) - tmp_x * sin(map->theta);
}

static void	rotate_x(int x, int y, t_map *map)
{
	double	tmp_y;

	tmp_y = map->point[y][x].y;
	map->point[y][x].y = tmp_y * cos(map->alpha) - \
		map->point[y][x].z * sin(map->alpha);
	map->point[y][x].z = tmp_y * sin(map->alpha) + \
		map->point[y][x].z * cos(map->alpha);
}

void	rotate_all(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			rotate_z(x, y, map);
			rotate_x(x, y, map);
			rotate_y(x, y, map);
			x++;
		}
		y++;
	}
}
