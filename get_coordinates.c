/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/12 16:39:56 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	init_map(t_map *map)
{
	map->memory = NULL;
	map->point = NULL;
	map->mem_alloc = false;
	map->point_alloc = false;
	map->len_x = 0;
	map->len_y = 0;
	map->x = 0;
	map->y = 0;
	map->z = 0;
}

int	get_coordinates(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;
	int		distance;
	int		offset;
	double	angle;

	y = 0;
	distance = (img->width / 2) / (map->len_x + map->len_y);
	offset = img->width / 2;
	angle = 0.7071;
	map->point = malloc(map->len_y * sizeof(t_point *));
	if (map->point == NULL)
		return (-1);
	while (y < map->len_y)
	{
		x = 0;
		map->point[y] = malloc(map->len_x * sizeof(t_point));
		if (map->point[y] == NULL)
			return (-1);
		while (x < map->len_x)
		{
			map->point[y][x].point_x = (x - y) * distance * angle + offset;
			map->point[y][x].point_y = (x + y) * distance * angle - map->memory[y][x] + offset;
			x++;
		}
		y++;
	}
	map->point_alloc = true;
	return (1);
}
