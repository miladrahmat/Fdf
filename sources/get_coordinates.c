/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/23 11:17:32 by mrahmat-         ###   ########.fr       */
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
			map->point[y][x].x += shift_x;
			map->point[y][x].y += shift_y;
			map->point[y][x].x += offset_x;
			map->point[y][x].y += offset_y;
			x++;
		}
		y++;
	}
}

static void	to_isometric(int x, int y, t_map *map)
{
	double	angle;
	double	axis_angle;

	angle = 30 * (PI / 180);
	axis_angle = 120 * (PI / 180);
	map->point[y][x].x = (x * cos(angle))
		+ (y * cos(angle + axis_angle))
		+ (map->point[y][x].z * cos(angle - axis_angle));
	map->point[y][x].y = (x * sin(angle))
		+ (y * sin(angle + axis_angle))
		+ (map->point[y][x].z * sin(angle - axis_angle));
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
			to_isometric(x * map->zoom, y * map->zoom, map);
			x++;
		}
		y++;
	}
	set_scale(map);
	find_min_coordinates(map, &min);
	shift_coordinates(map, -min.x, -min.y);
	return (1);
}
