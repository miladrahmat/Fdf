/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/24 17:11:00 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	fraction(double start, double end, double current)
{
	if (start != end)
		return ((current - start) / (end - start));
	return (0);
}

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
