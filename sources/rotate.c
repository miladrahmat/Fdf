/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:10:40 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/24 17:06:28 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(int x, int y, t_map *map)
{
	map->point[y][x].x = x * cos(map->gamma) - y * sin(map->gamma);
	map->point[y][x].y = x * sin(map->gamma) + y * cos(map->gamma);
}

void	rotate_y(int x, int y, t_map *map)
{
	map->point[y][x].x = x * cos(map->theta) \
		+ map->point[y][x].z * sin(map->theta);
	map->point[y][x].z = map->point[y][x].z * cos(map->theta) \
		- x * sin(map->theta);
}

void	rotate_x(int x, int y, t_map *map)
{
	map->point[y][x].y = y * cos(map->alpha) \
		- map->point[y][x].z * sin(map->alpha);
	map->point[y][x].z = y * sin(map->alpha) \
		+ map->point[y][x].z * cos(map->alpha);
}
