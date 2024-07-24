/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:22 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/24 15:30:15 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->window, MLX_KEY_ESCAPE))
		mlx_close_window(map->window);
	if (mlx_is_key_down(map->window, MLX_KEY_EQUAL) \
		|| mlx_is_key_down(map->window, MLX_KEY_MINUS))
		hook_zoom(map);
	if (mlx_is_key_down(map->window, MLX_KEY_UP) \
		|| mlx_is_key_down(map->window, MLX_KEY_DOWN) \
		|| mlx_is_key_down(map->window, MLX_KEY_LEFT) \
		|| mlx_is_key_down(map->window, MLX_KEY_RIGHT))
		hook_translate(map);
	if (mlx_is_key_down(map->window, MLX_KEY_S) \
		|| mlx_is_key_down(map->window, MLX_KEY_W) \
		|| mlx_is_key_down(map->window, MLX_KEY_D) \
		|| mlx_is_key_down(map->window, MLX_KEY_A))
		hook_rotate(map);
	draw_again(map);
}

void	hook_zoom(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_EQUAL))
		map->zoom += 0.1;
	if (mlx_is_key_down(map->window, MLX_KEY_MINUS) && map->zoom > 1)
		map->zoom -= 0.1;
}

void	hook_translate(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_UP))
		map->y_trans -= 5;
	if (mlx_is_key_down(map->window, MLX_KEY_DOWN))
		map->y_trans += 5;
	if (mlx_is_key_down(map->window, MLX_KEY_LEFT))
		map->x_trans -= 5;
	if (mlx_is_key_down(map->window, MLX_KEY_RIGHT))
		map->x_trans += 5;
}

void	hook_rotate(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_S))
	{
		map->theta -= 0.05;
		map->gamma -= 0.05;
	}
	if (mlx_is_key_down(map->window, MLX_KEY_W))
	{
		map->theta += 0.05;
		map->gamma += 0.05;
	}
	if (mlx_is_key_down(map->window, MLX_KEY_D))
	{
		map->alpha += 0.05;
		map->theta += 0.05;
		map->gamma += 0.05;
	}
	if (mlx_is_key_down(map->window, MLX_KEY_A))
	{
		map->alpha -= 0.05;
		map->theta -= 0.05;
		map->gamma -= 0.05;
	}
}
