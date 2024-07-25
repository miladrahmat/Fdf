/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/25 17:42:02 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	handle_images(t_map *map)
{
	map->img = mlx_new_image(map->window, map->window->width, \
		map->window->height);
	if (!map->img)
		return (-1);
	map->text = mlx_load_png("./includes/FDF.png");
	if (!map->text)
		return (-1);
	map->info_panel = mlx_texture_to_image(map->window, map->text);
	if (!map->info_panel)
	{
		mlx_delete_texture(map->text);
		return (-1);
	}
	draw_background(map);
	if (get_coordinates(map) < 0)
	{
		mlx_terminate(map->window);
		mlx_delete_texture(map->text);
		return (-1);
	}
	return (1);
}

static int	handle_window(t_map *map)
{
	map->window = mlx_init(1600, 1000, "FIL DE FER", true);
	if (!map->window)
		return (-1);
	if (handle_images(map) < 0)
	{
		mlx_terminate(map->window);
		return (-1);
	}
	draw_area(map);
	draw_map(map);
	mlx_image_to_window(map->window, map->img, map->info_panel->width, 0);
	mlx_image_to_window(map->window, map->info_panel, 0, 0);
	mlx_loop_hook(map->window, ft_hook, map);
	mlx_resize_hook(map->window, resize, map);
	mlx_loop(map->window);
	mlx_delete_texture(map->text);
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
			ft_putendl_fd("\e[1;31m Error in read_map() \e[0m", 2);
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
