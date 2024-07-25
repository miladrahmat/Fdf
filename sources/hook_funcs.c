/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:31:20 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/25 17:35:55 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	resize(int32_t width, int32_t height, void *param)
{
	t_map	*map;

	map = param;
	mlx_delete_image(map->window, map->img);
	map->img = mlx_new_image(map->window, width, height);
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
	mlx_resize_image(map->info_panel, width / 5, height);
	mlx_image_to_window(map->window, map->img, map->info_panel->width, 0);
	mlx_image_to_window(map->window, map->info_panel, 0, 0);
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
