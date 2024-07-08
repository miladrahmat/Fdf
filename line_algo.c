/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/08 13:42:02 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

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

static void	slope_less(mlx_image_t *img, t_draw *line, uint32_t color)
{
	int	p;
	int	i;

	p = 2 * absolute(line->dy) - absolute(line->dx);
	i = 0;
	while (i < absolute(line->dx))
	{
		mlx_put_pixel(img, line->start_x, line->start_y, color);
		line->start_x += line->sx;
		if (p < 0)
			p = p + 2 * absolute(line->dy);
		else
		{
			p = p + 2 * absolute(line->dy) - 2 * absolute(line->dx);
			line->start_y += line->sy;
		}	
		i++;
	}
}

static void	slope_greater(mlx_image_t *img, t_draw *line, uint32_t color)
{
	int	p;
	int	i;

	p = 2 * absolute(line->dx) - absolute(line->dy);
	i = 0;
	while (i < absolute(line->dy))
	{
		mlx_put_pixel(img, line->start_x, line->start_y, color);
		line->start_y += line->sy;
		if (p < 0)
			p = p + 2 * absolute(line->dx);
		else
		{
			p = p + 2 * absolute(line->dx) - 2 * absolute(line->dy);
			line->start_x += line->sx;
		}
		i++;
	}
}

void	draw_line(mlx_image_t *img, int start_x, int start_y,
	int end_x, int end_y, uint32_t color)
{
	t_draw	line;

	line = init_draw(start_x, start_y, end_x, end_y);
	if (absolute(line.dx) > absolute(line.dy))
		slope_less(img, &line, color);
	else
		slope_greater(img, &line, color);
}

void	draw_map(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;
	int	tmp;
	int	draw;
	int	color;

	x = 0;
	y = 0;
	tmp = x;
	//x = (tmp - y) * cos(0.523599);
	draw = 0;
	color = get_rgba(255, 255, 255, 255);
	while (x < (int)img->width)
	{
		y = 0;//(tmp + y) * sin(0.523599);
		while (y < (int)img->height)
		{
			draw_line(img, x - map->len_x / 2, y - map->len_y / 2, x - map->len_x / 2 + 1, y - map->len_y / 2, color);
			draw_line(img, x - map->len_x / 2, y - map->len_y / 2, x - map->len_x / 2, y - map->len_y / 2 + 1, color);
			y++;
		}
		x++;
		draw++;
	}
}
