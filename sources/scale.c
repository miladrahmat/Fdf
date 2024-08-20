/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:46:12 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/20 15:14:33 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_coordinates(t_map *map, double scale)
{
	int	x;
	int	y;

	if (scale <= 0)
	{
		if (map->img->width / 2 > map->img->height / 2)
			scale = map->img->height / 2;
		else
			scale = map->img->width / 2;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->point[y][x].x *= scale;
			map->point[y][x].y *= scale;
			x++;
		}
		y++;
	}
}

void	set_scale(t_map *map)
{
	t_point	min;
	t_point	max;
	double	scale_x;
	double	scale_y;

	find_min_coordinates(map, &min);
	find_max_coordinates(map, &max);
	scale_x = (max.x - min.x) / (map->img->width / 2);
	scale_y = (max.y - min.y) / (map->img->height / 2);
	scale_coordinates(map, fmin(1 / scale_x, 1 / scale_y));
}

void	find_min_coordinates(t_map *map, t_point *min)
{
	int	x;
	int	y;

	y = 0;
	min->x = map->point[0][0].x;
	min->y = map->point[0][0].y;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->point[y][x].x < min->x)
				min->x = map->point[y][x].x;
			if (map->point[y][x].y < min->y)
				min->y = map->point[y][x].y;
			x++;
		}
		y++;
	}
}

void	find_max_coordinates(t_map *map, t_point *max)
{
	int	x;
	int	y;

	max->x = map->point[0][0].x;
	max->y = map->point[0][0].y;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->point[y][x].x > max->x)
				max->x = map->point[y][x].x;
			if (map->point[y][x].y > max->y)
				max->y = map->point[y][x].y;
			x++;
		}
		y++;
	}
}
