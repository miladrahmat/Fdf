/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/09 14:09:24 by mrahmat-         ###   ########.fr       */
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
	if (start_x < end_x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = end_y - start_y;
	if (start_y < end_y)
		line.sy = 1;
	else
		line.sy = -1;
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
	int	pix_x;
	int	pix_y;
	int	color;

	x = 0;
	y = 0;
	map->x = 0;
	map->y = 0;
	pix_x = img->width / map->len_x;
	pix_y = img->height / map->len_y;
	color = get_rgba(255, 255, 255, 255);
	while (map->y < map->len_y - 1)
	{
		x = 0;
		map->x = 0;
		while (map->x < map->len_x - 1)
		{
			draw_line(img, x, y, x + pix_x, y, color);
			draw_line(img, x, y, x, y + pix_y, color);
			x += pix_x;
			map->x++;
		}
		y += pix_y;
		map->y++;
	}
}

void	draw_area(mlx_image_t *img, t_map *map)
{
	int			color;
	int			len_x;
	int			len_y;
	uint32_t	x;
	uint32_t	y;

	color = get_rgba(255, 255, 255, 255);
	len_x = (img->width / map->len_x) * (map->len_x - 1);
	len_y = (img->height / map->len_y) * (map->len_y - 1);
	x = 0;
	y = 0;
	draw_line(img, x, y, len_x, y, color);
	draw_line(img, x, y, x, len_x, color);
	draw_line(img, len_x, y, len_x, len_y, color);
	draw_line(img, x, len_y, len_x, len_y, color);
}
