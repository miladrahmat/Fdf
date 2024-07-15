/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/15 16:11:15 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	to_isometric(int x, int y, t_map *map, mlx_image_t *img)
{
	int	distance;
	int	offset;

	distance = (img->width / 2) / (map->len_x + map->len_y);
	offset = img->width / 2;
	map->point[y][x].x = (x - y) * distance * cos(0.523599) + offset;
	map->point[y][x].y = (x + y) * distance * sin(0.523599) \
		- map->memory[y][x] + offset;
}

int	get_coordinates(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;

	y = 0;
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
			to_isometric(x, y, map, img);
			x++;
		}
		y++;
	}
	map->point_alloc = true;
	return (1);
}
