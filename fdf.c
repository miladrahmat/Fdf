/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:41 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/02 16:40:02 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	create_map(t_map *map, char **split)
{
	int	i;
	int	res;

	i = 0;
	while (split[i] != NULL)
	{
		res = ft_atoi(split[i]);
		ft_memcpy(&map->memory[map->len_y][map->x], &res, sizeof(res));
		map->x++;
		i++;
	}
	if (map->len_y == 0)
		map->len_x = map->x;
	if (map->x != map->len_x)
	{
		free_map(map, true);
		split_free(split);
		return (-1);
	}
	map->len_y++;
	split_free(split);
	return (1);
}

int	read_map(t_map *map, int fd, char **arg)
{
	char	**split;
	char	*gnl;
	int		size;

	size = get_size(fd, arg);
	if (size == -1)
		return (-1);
	map->memory = malloc(size * sizeof(int *));
	if (map->memory == NULL)
		return (-1);
	map->len_y = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		map->x = 0;
		map->memory[map->len_y] = malloc((ft_strlen(gnl) / 2) * sizeof(int));
		split = ft_split(gnl, ' ');
		free(gnl);
		if (split == NULL || *split == NULL || map->memory[map->len_y] == NULL)
		{
			free_map(map, true);
			return (-1);
		}
		if (create_map(map, split) < 0)
			return (-1);
		gnl = get_next_line(fd);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			fd;

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
	mlx = mlx_init(500, 500, "FDF_TEST", true);
	if (!mlx)
		exit(1);
	image = mlx_new_image(mlx, 250, 250);
	ft_memset(image->pixels, 255, image->width * image->height * sizeof(int32_t));
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
	printf("Putting image to window\n");
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	printf("Terminating\n");
	mlx_terminate(mlx);
	printf("Freeing map\n");
	free_map(&map, true);
	exit(0);
}
