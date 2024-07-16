/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/16 14:20:23 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_background(mlx_image_t *img)
{
	int			color;
	uint32_t	x;
	uint32_t	y;

	color = get_rgba(0, 0, 0, 255);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	handle_window(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(1000, 1000, "FIL DE FER", true);
	if (!mlx)
		return (-1);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
	{
		mlx_terminate(mlx);
		return (-1);
	}
	draw_background(img);
	if (get_coordinates(img, map) < 0)
	{
		mlx_terminate(mlx);
		return (-1);
	}
	draw_area(img, map);
	draw_map(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}

static void	handle_input(char **av, t_map *map)
{
	int	fd;

	if (ft_strnstr(av[1], ".fdf", ft_strlen(av[1])) != 0)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putendl_fd("\e[1;31m Unable to open file", 2);
			exit(1);
		}
		if (read_map(map, fd, av) < 0)
		{
			ft_putendl_fd("\e[1;31m Error in read_map()", 2);
			exit(1);
		}
		close(fd);
	}
	else
	{
		ft_putendl_fd("\e[1;31m Invalid file", 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_map		map;

	if (argc != 2)
	{
		ft_putendl_fd("\e[1;31m Invalid number of arguments", 2);
		exit(1);
	}
	init_map(&map);
	handle_input(argv, &map);
	if (handle_window(&map) < 0)
	{
		free_map(&map);
		exit(1);
	}
	free_map(&map);
	exit(0);
}
