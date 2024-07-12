/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/12 13:33:03 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	int		tmp;
	double	sin;
	double	cos;

	tmp = *x;
	sin = 0.7071;
	cos = 0.7071;
	*x = (tmp - *y) * cos;
	*y = (tmp + *y)  * sin - z;
}


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

int	absolute(int nbr)
{
	if (nbr > 0)
		return (nbr);
	return (nbr * -1);
}
