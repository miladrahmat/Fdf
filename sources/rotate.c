/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:10:40 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/23 14:24:52 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_map *map)
{
	int		x;
	int		y;
	double	tmp;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tmp = map->point[y][x].x;
			map->point[y][x].x += tmp * cos(map->gamma) \
				- map->point[y][x].y * sin(map->gamma);
			map->point[y][x].y += tmp * cos(map->gamma) \
				- map->point[y][x].y * sin(map->gamma);
		}
	}
}

void	rotate_y(t_map *map)
{
	int		x;
	int		y;
	double	tmp;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tmp = map->point[y][x].x;
			map->point[y][x].x += tmp * cos(map->theta) \
				- map->point[y][x].y * sin(map->theta);
			map->point[y][x].y += tmp * cos(map->theta) \
				- map->point[y][x].y * sin(map->theta);
		}
	}
}

void	rotate_x(t_map *map)
{
	int		x;
	int		y;
	double	tmp;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tmp = map->point[y][x].x;
			map->point[y][x].x += tmp * cos(map->alpha) \
				- map->point[y][x].y * sin(map->alpha);
			map->point[y][x].y += tmp * cos(map->alpha) \
				- map->point[y][x].y * sin(map->alpha);
		}
	}
}
