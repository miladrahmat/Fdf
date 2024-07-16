/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/16 18:27:11 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* int	convert_rgba(int color)
{
	
} */

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->point_alloc == true)
	{
		while (i < map->height)
		{
			free(map->point[i]);
			i++;
		}
	}
	free(map->point);
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
	map->x = 0;
	map->y = 0;
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
