/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/05 17:14:24 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*grid;
	mlx_image_t	*back;
	int			fd;
	int			pix;

	if (argc < 2)
		exit(1);
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		if (read_map(&map, fd, argv) < 0)
			exit (1);
	}
	else
		exit(1);
	mlx = mlx_init(2000, 2000, "FDF_TEST", true);
	if (!mlx)
	{
		free_map(&map, true);
		exit(1);
	}
	pix = ft_sqrt(map.len_x, map.len_y);
	grid = mlx_new_image(mlx, 1000, 1000);
	back = mlx_new_image(mlx, 2000, 2000);
	draw_x(back, 0, 0, back->width, back->height, 1, get_rgba(0, 0, 0, 255));
	mlx_image_to_window(mlx, back, 0, 0);
	draw_map(grid, &map);
	//draw_x(grid, 0, 0, map.len_x * 40, map.len_y, 40, get_rgba(255, 255, 255, 255));
	//draw_y(grid, 0, 0, map.len_x, map.len_y * 40, 40, get_rgba(255, 255, 255, 255));
	//draw_line(grid, 0, 0, 0, 1000, get_rgba(255, 255, 255, 255));
	mlx_image_to_window(mlx, grid, 600, 700);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	free_map(&map, true);
	mlx_terminate(mlx);
	exit(0);
}
