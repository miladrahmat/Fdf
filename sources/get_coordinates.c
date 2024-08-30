/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 16:41:51 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	shift_coordinates(t_map *map, double shift_x, double shift_y)
{
	int		x;
	int		y;

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
			x++;
		}
		y++;
	}
}

static void	to_isometric(int x, int y, t_map *map)
{
	double	temp_x;

	temp_x = map->point[y][x].x;
	map->point[y][x].x = (temp_x - map->point[y][x].y) * \
		cos(0.523599);
	map->point[y][x].y = (temp_x + map->point[y][x].y) * \
		sin(0.523599) - map->point[y][x].z;
}

static void	to_orthographic(int x, int y, t_map *map)
{
	if (map->top == true)
	{
		map->point[y][x].x = map->point[y][x].x;
		map->point[y][x].y = map->point[y][x].y;
	}
	else if (map->front == true)
	{
		map->point[y][x].x = map->point[y][x].x;
		map->point[y][x].y = -map->point[y][x].z;
	}
	else if (map->right == true)
	{
		map->point[y][x].x = map->point[y][x].y;
		map->point[y][x].y = -map->point[y][x].z;
	}
}

void	scale_z(t_map *map)
{
	int	scale;
	int	x;
	int	y;

	find_min_max_z(map);
	scale = map->max_z - map->min_z;
	if (scale == 0)
		scale = 1;
	scale = ((map->img->height / 10) + (map->img->width / 10)) / scale;
	if (scale == 0)
		scale = 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->point[y][x].z = map->backup[y][x].z * scale;
			x++;
		}
		y++;
	}
}

int	get_coordinates(t_map *map)
{
	t_point	min;
	int		x;
	int		y;

	inital_points(map);
	set_scale(map);
	rotate_all(map);
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
	find_min_coordinates(map, &min);
	shift_coordinates(map, -min.x, -min.y);
	center_map(map);
	return (1);
}
