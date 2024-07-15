/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/15 14:06:09 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	slope_less(mlx_image_t *img, t_draw *line, uint32_t color)
{
	int	p;
	int	i;

	p = 2 * abs(line->dy) - abs(line->dx);
	i = 0;
	while (i < abs(line->dx))
	{
		mlx_put_pixel(img, line->start_x, line->start_y, color);
		line->start_x += line->sx;
		if (p < 0)
			p = p + 2 * abs(line->dy);
		else
		{
			p = p + 2 * abs(line->dy) - 2 * abs(line->dx);
			line->start_y += line->sy;
		}
		i++;
	}
}

static void	slope_greater(mlx_image_t *img, t_draw *line, uint32_t color)
{
	int	p;
	int	i;

	p = 2 * abs(line->dx) - abs(line->dy);
	i = 0;
	while (i < abs(line->dy))
	{
		mlx_put_pixel(img, line->start_x, line->start_y, color);
		line->start_y += line->sy;
		if (p < 0)
			p = p + 2 * abs(line->dx);
		else
		{
			p = p + 2 * abs(line->dx) - 2 * abs(line->dy);
			line->start_x += line->sx;
		}
		i++;
	}
}

void	draw_line(mlx_image_t *img, t_draw *line, uint32_t color)
{
	if (abs(line->dx) > abs(line->dy))
		slope_less(img, line, color);
	else
		slope_greater(img, line, color);
}

void	draw_map(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;
	int		color;
	t_draw	line;

	y = 0;
	color = get_rgba(255, 255, 255, 255);
	while (y < map->len_y - 1)
	{
		x = 0;
		while (x < map->len_x - 1)
		{
			line = init_draw(map->point[y][x].x, map->point[y][x].y, \
				map->point[y][x + 1].x, map->point[y][x + 1].y);
			draw_line(img, &line, color);
			line = init_draw(map->point[y][x].x, map->point[y][x].y, \
				map->point[y + 1][x].x, map->point[y + 1][x].y);
			draw_line(img, &line, color);
			x++;
		}
		y++;
	}
}

void	draw_area(mlx_image_t *img, t_map *map)
{
	int		color;
	t_draw	line;

	color = get_rgba(255, 255, 255, 255);
	line = init_draw(map->point[0][0].x, \
		map->point[0][0].y, \
		map->point[0][map->len_x - 1].x, \
		map->point[0][map->len_x - 1].y);
	draw_line(img, &line, color);
	line = init_draw(map->point[0][map->len_x - 1].x, \
		map->point[0][map->len_x - 1].y, \
		map->point[map->len_y - 1][map->len_x - 1].x, \
		map->point[map->len_y - 1][map->len_x - 1].y);
	draw_line(img, &line, color);
	line = init_draw(map->point[map->len_y - 1][0].x, \
		map->point[map->len_y - 1][0].y, \
		map->point[map->len_y - 1][map->len_x - 1].x, \
		map->point[map->len_y - 1][map->len_x - 1].y);
	draw_line(img, &line, color);
	line = init_draw(map->point[0][0].x, \
		map->point[0][0].y, \
		map->point[map->len_y - 1][0].x, \
		map->point[map->len_y - 1][0].y);
	draw_line(img, &line, color);
}
