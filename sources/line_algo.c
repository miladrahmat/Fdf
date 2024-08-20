/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:09:27 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/20 15:14:56 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	slope_less(mlx_image_t *img, t_draw *line, \
	t_point *start, t_point *end)
{
	int			p;
	int			i;
	double		x;
	double		y;
	uint32_t	color;

	p = 2 * abs(line->dy) - abs(line->dx);
	i = 0;
	x = line->start_x;
	y = line->start_y;
	while (i++ < abs(line->dx))
	{
		line->fraction = fraction(line->start_x, line->end_x, x);
		color = calculate_color(start, end, line);
		if ((x > 0 && x < img->width) && (y > 0 && y < img->height))
			mlx_put_pixel(img, x, y, color);
		x += line->sx;
		if (p < 0)
			p = p + 2 * abs(line->dy);
		else
		{
			p = p + 2 * abs(line->dy) - 2 * abs(line->dx);
			y += line->sy;
		}
	}
}

static void	slope_greater(mlx_image_t *img, t_draw *line, \
	t_point *start, t_point *end)
{
	int			p;
	int			i;
	double		x;
	double		y;
	uint32_t	color;

	p = 2 * abs(line->dx) - abs(line->dy);
	i = 0;
	x = line->start_x;
	y = line->start_y;
	while (i++ < abs(line->dy))
	{
		line->fraction = fraction(line->start_y, line->end_y, y);
		color = calculate_color(start, end, line);
		if ((x > 0 && x < img->width) && (y > 0 && y < img->height))
			mlx_put_pixel(img, x, y, color);
		y += line->sy;
		if (p < 0)
			p = p + 2 * abs(line->dx);
		else
		{
			p = p + 2 * abs(line->dx) - 2 * abs(line->dy);
			x += line->sx;
		}
	}
}

void	draw_line(mlx_image_t *img, t_draw *line, t_point *start, t_point *end)
{
	if (abs(line->dx) > abs(line->dy))
		slope_less(img, line, start, end);
	else
		slope_greater(img, line, start, end);
}

void	draw_map(t_map *map)
{
	int		x;
	int		y;
	t_draw	line;

	y = 0;
	while (y < map->height - 1)
	{
		x = 0;
		while (x < map->width - 1)
		{
			line = init_draw(map->point[y][x].x, map->point[y][x].y, \
				map->point[y][x + 1].x, map->point[y][x + 1].y);
			draw_line(map->img, &line, &map->point[y][x], \
				&map->point[y][x + 1]);
			line = init_draw(map->point[y][x].x, map->point[y][x].y, \
				map->point[y + 1][x].x, map->point[y + 1][x].y);
			draw_line(map->img, &line, &map->point[y][x], \
				&map->point[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	draw_area(t_map *map)
{
	int		x;
	int		y;
	t_draw	line;

	y = map->height - 1;
	x = 0;
	while (x < map->width - 1)
	{
		line = init_draw(map->point[y][x].x, map->point[y][x].y, \
			map->point[y][x + 1].x, map->point[y][x + 1].y);
		draw_line(map->img, &line, &map->point[y][x], &map->point[y][x + 1]);
		x++;
	}
	y = 0;
	x = map->width - 1;
	while (y < map->height - 1)
	{
		line = init_draw(map->point[y][x].x, map->point[y][x].y, \
			map->point[y + 1][x].x, map->point[y + 1][x].y);
		draw_line(map->img, &line, &map->point[y][x], &map->point[y + 1][x]);
		y++;
	}
}
