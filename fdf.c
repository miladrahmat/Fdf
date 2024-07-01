/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/01 18:00:52 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		**split;
	char		*gnl;
	int			res;
	int			fd;
	int 		s_i;
	int			arr_i;
	int			w_i;
	int			check;

	s_i = 0;
	arr_i = 0;
	w_i = 0;
	check = 0;
	if (argc < 2)
		exit(1);
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		gnl = get_next_line(fd);
		map.memory = malloc(10 * sizeof(int *));
		if (gnl == NULL || map.memory == NULL)
		{
			close(fd);
			exit(1);
		}
		while (gnl != NULL)
		{
			w_i = 0;
			s_i = 0;
			split = ft_split(gnl, ' ');
			if (split == NULL || *split == NULL)
			{
				free(gnl);
				free(map.memory);
				close(fd);
				exit(1);
			}
			map.memory[arr_i] = malloc(ft_strlen(gnl) * sizeof(int));
			free(gnl);
			if (*map.memory == NULL)
			{
				split_free(split);
				exit(1);
			}
			while (split[s_i] != NULL)
			{
				res = ft_atoi(split[s_i]);
				ft_memcpy(&map.memory[arr_i][w_i], &res, sizeof(res));
				s_i++;
				w_i++;
			}
			if (check == 0)
				map.len_x = w_i;
			if (map.len_x != w_i)
			{
				free(gnl);
				split_free(split);
				exit(1);
			}
			arr_i++;
			split_free(split);
			gnl = get_next_line(fd);
		}
		map.len_y = arr_i;
		close(fd);
	}
	else
		exit(1);
	mlx = mlx_init(256, 256, "FDF_TEST", true);
	if (!mlx)
		exit(1);
	image = mlx_new_image(mlx, map.len_x, map.len_y);
	map.y = 0;
	while (map.y < map.len_y)
	{
		map.x = 0;
		while (map.x < map.len_x)
		{
			if (map.memory[map.y][map.x] == 0)
				mlx_put_pixel(image, map.x, map.y, get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(image, map.x, map.y, get_rgba(0, 0, 0, 255));
			map.x++;
		}
		map.y++;
	}
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	while (map.len_y-- > 0)
		free(map.memory[map.len_y]);
	free(map.memory);
	exit(0);
}
