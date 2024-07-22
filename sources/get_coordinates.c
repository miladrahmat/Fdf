/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/22 18:21:15 by mrahmat-         ###   ########.fr       */
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
			map->point[y][x].x += shift_x;
			map->point[y][x].y += shift_y;
			//map->point[y][x].x += 1600 / 3;
			//map->point[y][x].y += 1000 / 2;
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

/* static void	to_isometric(int x, int y, t_map *map, mlx_image_t *img)
{
	int	distance;

	distance = (img->width / 2) / (map->width + map->height);
	map->point[y][x].x = (x - y) * distance * cos(30 * (PI / 180));
	map->point[y][x].y = (x + y) * distance * sin(120 * (PI / 180)) \
		- map->point[y][x].z;
} */

int	get_coordinates(mlx_image_t *img, t_map *map)
{
	t_point	min;
	int		x;
	int		y;
	int		scale;

	scale = scale_z(map, img);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			//map->point[y][x].z = map->point[y][x].z * (scale / 2);
			to_isometric(x, y, map);
			x++;
		}
		y++;
	}
	set_scale(map, img);
	find_min_coordinates(map, &min);
	shift_coordinates(map, -min.x, -min.y);
	return (1);
}

int	find_max_z(t_map *map)
{
	int	x;
	int	y;
	int	max;

	max = INT_MIN;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->point[y][x].z > max)
				max = map->point[y][x].z;
			x++;
		}
		y++;
	}
	return (max);
}
