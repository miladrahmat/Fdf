/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/18 14:48:51 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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
	a = start->a + (end->a - start->a) * line->fraction;
	color = get_rgba(r, g, b, a);
	return (color);
}

int	determine_base(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			return (2);
		if (str[i] >= 'a' && str[i] <= 'f')
			return (1);
		i++;
	}
	return (1);
}

int	get_color(t_map *map, char *str)
{
	char			**split;
	char			*rgba;

	split = ft_split(str, ',');
	if (split == NULL || *split == NULL)
		return (-1);
	map->point[map->height][map->x].z = ft_atoi(split[0]);
	rgba = add_alpha(split[1]);
	map->point[map->height][map->x].color = ft_atoi_base(rgba + 2, 16);
	convert_to_rgba(&map->point[map->height][map->x]);
	free(rgba);
	split_free(split);
	return (1);
}
