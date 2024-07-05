/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/05 16:58:15 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_sqrt(int x, int y)
{
	int	res;
	int	sqrt;

	res = ((x * x) + (y * y));
	sqrt = 0;
	while ((sqrt * sqrt) != res)
	{
		if ((sqrt * sqrt) > res)
		{
			return (sqrt);
		}
		sqrt++;
	}
	return (sqrt);
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_x(mlx_image_t *img, int x, int y,
	int end_x, int end_y, int pix, uint32_t color)
{
	int	use_x;
	int	draw;

	use_x = x;
	draw = 0;
	while (draw < end_y)
	{
		while (use_x < end_x)
		{
			//draw_line(img, use_x, y, end_x, end_y, color);
			mlx_put_pixel(img, use_x, y, color);
			use_x++;
		}
		draw++;
		y += pix;
		use_x = x;
	}
}

void	draw_y(mlx_image_t *img, int x, int y,
	int end_x, int end_y, int pix, uint32_t color)
{
	int	use_y;
	int	draw;

	use_y = y;
	draw = 0;
	while (draw < end_x)
	{
		while (use_y < end_y)
		{
			//draw_line(img, x, use_y, end_x, end_y, color);
			mlx_put_pixel(img, x, use_y, color);
			use_y++;
		}
		draw++;
		x += pix;
		use_y = y;
	}
}
