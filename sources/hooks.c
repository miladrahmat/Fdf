/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:22 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/23 14:23:26 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->window, MLX_KEY_ESCAPE))
		mlx_close_window(map->window);
	if (mlx_is_key_down(map->window, MLX_KEY_EQUAL))
	{
		map->zoom += 0.1;
		draw_again(map);
	}
	if (mlx_is_key_down(map->window, MLX_KEY_MINUS) && map->zoom > 1)
	{
		map->zoom -= 0.1;
		draw_again(map);
	}
	hook_translate(map);
}

void	hook_translate(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_UP))
	{
		map->y_trans -= 5;
		draw_again(map);
	}
	if (mlx_is_key_down(map->window, MLX_KEY_DOWN))
	{
		map->y_trans += 5;
		draw_again(map);
	}
	if (mlx_is_key_down(map->window, MLX_KEY_LEFT))
	{
		map->x_trans -= 5;
		draw_again(map);
	}
	if (mlx_is_key_down(map->window, MLX_KEY_RIGHT))
	{
		map->x_trans += 5;
		draw_again(map);
	}
}

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
	mlx_image_to_window(map->window, map->img, 0, 0);
}

void	draw_again(void *param)
{
	t_map	*map;

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
	mlx_image_to_window(map->window, map->img, 0, 0);
}
