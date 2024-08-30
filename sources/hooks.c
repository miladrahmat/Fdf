/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:22 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 16:37:32 by mrahmat-         ###   ########.fr       */
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
	if (mlx_is_key_down(map->window, MLX_KEY_Q) \
		|| mlx_is_key_down(map->window, MLX_KEY_E) \
		|| mlx_is_key_down(map->window, MLX_KEY_D) \
		|| mlx_is_key_down(map->window, MLX_KEY_A)
		|| mlx_is_key_down(map->window, MLX_KEY_Z)
		|| mlx_is_key_down(map->window, MLX_KEY_C))
		hook_rotate(map);
	if (mlx_is_key_down(map->window, MLX_KEY_1) \
		|| mlx_is_key_down(map->window, MLX_KEY_2) \
		|| mlx_is_key_down(map->window, MLX_KEY_3) \
		|| mlx_is_key_down(map->window, MLX_KEY_R))
		hook_projection(map);
}

void	hook_zoom(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_EQUAL))
		map->zoom += 0.05;
	if (mlx_is_key_down(map->window, MLX_KEY_MINUS) && map->zoom > 0.05)
		map->zoom -= 0.05;
	draw_again(map);
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
	draw_again(map);
}

void	hook_rotate(t_map *map)
{
	if (mlx_is_key_down(map->window, MLX_KEY_Q) && map->isometric == true)
		map->alpha -= 0.02;
	if (mlx_is_key_down(map->window, MLX_KEY_E) && map->isometric == true)
		map->alpha += 0.02;
	if (mlx_is_key_down(map->window, MLX_KEY_A))
		map->gamma -= 0.02;
	if (mlx_is_key_down(map->window, MLX_KEY_D))
		map->gamma += 0.02;
	if (mlx_is_key_down(map->window, MLX_KEY_Z) && map->isometric == true)
		map->theta -= 0.02;
	if (mlx_is_key_down(map->window, MLX_KEY_C) && map->isometric == true)
		map->theta += 0.02;
	draw_again(map);
}

void	hook_projection(t_map *map)
{
	map->isometric = false;
	map->top = false;
	map->front = false;
	map->right = false;
	map->gamma = 0;
	map->alpha = 0;
	map->theta = 0;
	if (mlx_is_key_down(map->window, MLX_KEY_1))
		map->top = true;
	if (mlx_is_key_down(map->window, MLX_KEY_3))
		map->right = true;
	if (mlx_is_key_down(map->window, MLX_KEY_2))
		map->front = true;
	if (mlx_is_key_down(map->window, MLX_KEY_R))
	{
		map->isometric = true;
		map->alpha = 0;
		map->theta = 0;
		map->gamma = 0;
		map->x_trans = 0;
		map->y_trans = 0;
	}
	draw_again(map);
}
