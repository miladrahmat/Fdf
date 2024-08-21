/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:31:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/21 12:38:34 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_again(void *param)
{
	t_map	*map;
	int32_t	depth;

	map = param;
	mlx_delete_image(map->window, map->img);
	map->img = mlx_new_image(map->window, map->window->width, \
		map->window->height);
	if (!map->img)
	{
		mlx_terminate(map->window);
		free_map(map, 0);
		exit(1);
	}
	draw_background(map);
	if (get_coordinates(map) < 0)
	{
		mlx_terminate(map->window);
		free_map(map, 0);
		exit(1);
	}
	draw_area(map);
	draw_map(map);
	depth = mlx_image_to_window(map->window, map->img, 0, 0);
	mlx_set_instance_depth(map->img->instances, depth - 1);
}
