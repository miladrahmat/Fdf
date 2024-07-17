/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:46 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	convert_to_rgba(t_point *point)
{
	point->r = (point->color >> 24) & 0xFF;
	point->g = (point->color >> 16) & 0xFF;
	point->b = (point->color >> 8) & 0xFF;
	point->a = point->color & 0xFF;
}

uint32_t	calculate_color(t_point *start, t_point *end, t_draw *line)
{
	uint32_t	color;
	int			r;
	int			g;
	int			b;
	int			a;

	r = start->r + (end->r - start->r) * line->fraction;
	g = start->g + (end->g - start->g) * line->fraction;
	b = start->b + (end->b - start->b) * line->fraction;
	a = start->a;
	color = get_rgba(r, g, b, a);
	return (color);
}