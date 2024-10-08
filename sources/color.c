/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/29 13:53:39 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*add_alpha(char *str)
{
	char	*rgba;
	char	*nl;

	if (ft_strchr(str, '\n') != 0)
	{
		nl = ft_substr(str, 0, ft_strlen(str) - 1);
		if (determine_base(str) == 1)
			rgba = ft_strjoin(nl, "ff");
		else
			rgba = ft_strjoin(nl, "FF");
		free(nl);
	}
	else
	{
		if (determine_base(str) == 1)
			rgba = ft_strjoin(str, "ff");
		else
			rgba = ft_strjoin(str, "FF");
	}
	return (rgba);
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
	int			r;
	int			g;
	int			b;
	int			a;

	r = start->r + (end->r - start->r) * line->fraction;
	g = start->g + (end->g - start->g) * line->fraction;
	b = start->b + (end->b - start->b) * line->fraction;
	a = start->a + (end->a - start->a) * line->fraction;
	return (r << 24 | g << 16 | b << 8 | a);
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

int	get_color(t_map *map, char *str, int index)
{
	char			**split;
	char			*rgba;

	split = ft_split(str, ',');
	if (split == NULL || *split == NULL)
		return (-1);
	map->point[map->height][index].z = ft_atoi(split[0]);
	rgba = add_alpha(split[1]);
	map->point[map->height][index].color = ft_atoi_base(rgba + 2, 16);
	convert_to_rgba(&map->point[map->height][index]);
	free(rgba);
	split_free(split);
	return (1);
}
