/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:31:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/20 14:00:22 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	resize(int32_t width, int32_t height, void *param)
{
	t_map	*map;

	map = param;
	mlx_resize_image(map->img, width, height);
}

void	draw_again(void *param)
{
	t_map	*map;

	map = param;
	mlx_delete_image(map->window, map->img);
	map->img = mlx_new_image(map->window, map->window->width \
		- map->info_panel->width, map->window->height);
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
	mlx_image_to_window(map->window, map->img, map->info_panel->width, 0);
	mlx_image_to_window(map->window, map->info_panel, 0, 0);
}
