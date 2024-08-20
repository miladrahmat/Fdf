/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/20 15:14:46 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	shift_coordinates(t_map *map, double shift_x, double shift_y)
{
	int		x;
	int		y;
	int		offset_x;
	int		offset_y;

	offset_x = map->img->width / 3;
	offset_y = map->img->height / 3;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->point[y][x].x *= map->zoom;
			map->point[y][x].y *= map->zoom;
			map->point[y][x].x += shift_x;
			map->point[y][x].y += shift_y;
			map->point[y][x].x += offset_x;
			map->point[y][x].y += offset_y;
			map->point[y][x].x += map->x_trans;
			map->point[y][x].y += map->y_trans;
			x++;
		}
		y++;
	}
}

static void	to_isometric(int x, int y, t_map *map)
{
	map->point[y][x].x = (x * cos(map->alpha))
		+ (y * cos(map->theta))
		+ (map->point[y][x].z * cos(map->gamma));
	map->point[y][x].y = (x * sin(map->alpha))
		+ (y * sin(map->theta))
		+ (map->point[y][x].z * sin(map->gamma));
}

static void	to_orthographic(int x, int y, t_map *map)
{
	if (map->top == true)
	{
		map->point[y][x].x = x;
		map->point[y][x].y = y;
	}
	else if (map->front == true)
	{
		map->point[y][x].x = x;
		map->point[y][x].y = -map->point[y][x].z;
	}
	else if (map->right == true)
	{
		map->point[y][x].x = y;
		map->point[y][x].y = -map->point[y][x].z;
	}
}

int	get_coordinates(t_map *map)
{
	t_point	min;
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->isometric == true)
				to_isometric(x, y, map);
			else
				to_orthographic(x, y, map);
			x++;
		}
		y++;
	}
	set_scale(map);
	find_min_coordinates(map, &min);
	shift_coordinates(map, -min.x, -min.y);
	return (1);
}
