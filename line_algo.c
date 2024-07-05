/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/05 17:57:07 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_draw	init_draw(int start_x, int start_y, int end_x, int end_y)
{
	t_draw	line;

	line.start_x = start_x;
	line.start_y = start_y;
	line.end_x = end_x;
	line.end_y = end_y;
	line.dx = start_x - end_x;
	if (line.dx < 0)
		line.dx *= -1;
	if (start_x < end_x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = end_y - start_y;
	if (line.dy > 0)
		line.dy *= -1;
	if (start_y < end_y)
		line.sy = 1;
	else
		line.sy = -1;
	line.e = line.dx + line.dy;
	return (line);
}

void	draw_line(mlx_image_t *img, int start_x, int start_y,
	int end_x, int end_y, uint32_t color)
{
	t_draw	line;

	line = init_draw(start_x, start_y, end_x, end_y);
	while (line.start_x != line.end_x || line.start_y != line.end_y)
	{
		mlx_put_pixel(img, line.start_x, line.start_y, color);
		line.e2 = line.e + line.e;
		if (line.e2 >= line.dy)
		{
			if (line.start_x == line.end_x)
				break ;
			line.e = line.e + line.dy;
			line.start_x = line.start_x + line.sx;
		}
		if (line.e2 <= line.dx)
		{
			if (line.start_y == line.end_y)
				break ;
			line.e = line.e + line.dx;
			line.start_y = line.start_y + line.sy;
		}
	}
}

void	draw_map(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;
	int	draw;
	int	color;

	x = 0;
	draw = 0;
	color = get_rgba(255, 255, 255, 255);
	while (draw < map->len_x)
	{
		y = 0;
		while (y < map->len_y)
		{
			draw_line(img, x, y, map->len_x, img->height, color);
			draw_line(img, x, y, x, img->height, color);
			y += 40;
		}
		x += 40;
		draw++;
	}
}
