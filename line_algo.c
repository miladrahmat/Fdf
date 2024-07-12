/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/12 17:32:26 by mrahmat-         ###   ########.fr       */
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
	int	color;

	y = 0;
	color = get_rgba(255, 255, 255, 255);
	while (y < map->len_y - 1)
	{
		x = 0;
		while (x < map->len_x - 1)
		{
			draw_line(img, map->point[y][x].point_x, map->point[y][x].point_y, map->point[y][x + 1].point_x, map->point[y][x + 1].point_y, color);
			draw_line(img, map->point[y][x].point_x, map->point[y][x].point_y, map->point[y + 1][x].point_x, map->point[y + 1][x].point_y, color);
			x++;
		}
		y++;
	}
}

void	draw_area(mlx_image_t *img, t_map *map)
{
	int		color;
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;

	color = get_rgba(255, 255, 255, 255);
	start_x = map->point[0][0].point_x;
	start_y = map->point[0][0].point_y;
	end_x = map->point[0][map->len_x - 1].point_x;
	end_y = map->point[0][map->len_x - 1].point_y;
	draw_line(img, start_x, start_y, end_x, end_y, color);
	start_x = map->point[0][map->len_x - 1].point_x;
	start_y = map->point[0][map->len_x - 1].point_y;
	end_x = map->point[map->len_y - 1][map->len_x - 1].point_x;
	end_y = map->point[map->len_y - 1][map->len_x - 1].point_y;
	draw_line(img, start_x, start_y, end_x, end_y, color);
	start_x = map->point[map->len_y - 1][0].point_x;
	start_y = map->point[map->len_y - 1][0].point_y;
	end_x = map->point[map->len_y - 1][map->len_x - 1].point_x;
	end_y = map->point[map->len_y - 1][map->len_x - 1].point_y;
	draw_line(img, start_x, start_y, end_x, end_y, color);
	start_x = map->point[0][0].point_x;
	start_y = map->point[0][0].point_y;
	end_x = map->point[map->len_y - 1][0].point_x;
	end_y = map->point[map->len_y - 1][0].point_y;
	draw_line(img, start_x, start_y, end_x, end_y, color);
}
