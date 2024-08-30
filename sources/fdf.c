/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 16:29:02 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_instructions(t_map *map)
{
	mlx_put_string(map->window, "FDF", 5, 10);
	mlx_put_string(map->window, "Translation", 5, 40);
	mlx_put_string(map->window, "Up arrow key:\tMove up", 5, 60);
	mlx_put_string(map->window, "Down arrow key:\tMove down", 5, 80);
	mlx_put_string(map->window, "Left arrow key:\tMove left", 5, 100);
	mlx_put_string(map->window, "Right arrow key:\tMove right", 5, 120);
	mlx_put_string(map->window, "Rotation", 5, 150);
	mlx_put_string(map->window, "Q and E keys:\tRotate X axis \
		(Only in isometric projection)", 5, 170);
	mlx_put_string(map->window, "Z and C keys:\tRotate Y axis \
		(Only in isometric projection)", 5, 190);
	mlx_put_string(map->window, "A and D keys:\tRotate Z axis", 5, 210);
	mlx_put_string(map->window, "Zooming", 5, 230);
	mlx_put_string(map->window, "+ key:\tZoom in", 5, 260);
	mlx_put_string(map->window, "- key:\tZoom out", 5, 280);
	mlx_put_string(map->window, "Projections:", 5, 300);
	mlx_put_string(map->window, "Orthographic projection:", 5, 330);
	mlx_put_string(map->window, "1 key:\tTop view", 5, 360);
	mlx_put_string(map->window, "2 key:\tFront view", 5, 380);
	mlx_put_string(map->window, "3 key:\tRight side view", 5, 400);
	mlx_put_string(map->window, "Isometric projection", 5, 420);
	mlx_put_string(map->window, "R key:\tReset back to isometric projection", \
		5, 450);
}

static int	handle_images(t_map *map)
{
	map->img = mlx_new_image(map->window, map->window->width, \
		map->window->height);
	if (!map->img)
		return (-1);
	draw_background(map);
	if (get_backup(map) < 0)
		return (-1);
	scale_z(map);
	if (get_coordinates(map) < 0)
	{
		mlx_terminate(map->window);
		return (-1);
	}
	draw_area(map);
	draw_map(map);
	return (1);
}

static int	handle_window(t_map *map)
{
	int32_t	depth;

	map->window = mlx_init(1600, 1000, "FIL DE FER", true);
	if (!map->window)
		return (-1);
	set_instructions(map);
	if (handle_images(map) < 0)
	{
		mlx_terminate(map->window);
		return (-1);
	}
	depth = mlx_image_to_window(map->window, map->img, 0, 0);
	mlx_set_instance_depth(map->img->instances, depth - 1);
	mlx_loop_hook(map->window, ft_hook, map);
	mlx_resize_hook(map->window, resize, map);
	mlx_loop(map->window);
	mlx_terminate(map->window);
	return (1);
}

static int	handle_input(char **av, t_map *map)
{
	int	fd;

	if (ft_strnstr(av[1], ".fdf", ft_strlen(av[1])) != 0)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putendl_fd("\e[1;31m Unable to open file \e[0m", 2);
			return (-1);
		}
		if (read_map(map, fd, av) < 0)
		{
			free_gnl(fd);
			ft_putendl_fd("\e[1;31m Error in read_map() \e[0m", 2);
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else
	{
		ft_putendl_fd("\e[1;31m Invalid file \e[0m", 2);
		exit(1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map;

	if (argc != 2)
	{
		ft_putendl_fd("\e[1;31m Invalid number of arguments \e[0m", 2);
		exit(1);
	}
	init_map(&map);
	if (handle_input(argv, &map) < 0)
	{
		free_map(&map, 1);
		exit (1);
	}
	if (handle_window(&map) < 0)
	{
		free_map(&map, 0);
		exit(1);
	}
	free_map(&map, 0);
	exit(0);
}
