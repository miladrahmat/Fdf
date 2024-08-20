/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/20 15:14:41 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_map *map)
{
	int			color;
	uint32_t	x;
	uint32_t	y;

	color = 0x000000FF;
	y = 0;
	while (y < map->img->height)
	{
		x = 0;
		while (x < map->img->width)
		{
			mlx_put_pixel(map->img, x, y, color);
			x++;
		}
		y++;
	}
}

double	fraction(double start, double end, double current)
{
	if (start != end)
		return ((current - start) / (end - start));
	return (0);
}

void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr[i]);
	free(arr);
	arr = NULL;
}

void	init_map(t_map *map)
{
	map->point = NULL;
	map->point_alloc = false;
	map->isometric = true;
	map->width = 0;
	map->height = 0;
	map->zoom = 1;
	map->x_trans = 0;
	map->y_trans = 0;
	map->alpha = 30 * (PI / 180);
	map->gamma = (30 * (PI / 180) - (120 * (PI / 180)));
	map->theta = (30 * (PI / 180) + (120 * (PI / 180)));
}

t_draw	init_draw(int start_x, int start_y, int end_x, int end_y)
{
	t_draw	line;

	line.start_x = start_x;
	line.start_y = start_y;
	line.end_x = end_x;
	line.end_y = end_y;
	line.dx = end_x - start_x;
	if (start_x < end_x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = start_y - end_y;
	if (start_y < end_y)
		line.sy = 1;
	else
		line.sy = -1;
	return (line);
}
