/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/16 18:40:01 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	to_isometric(int x, int y, t_map *map, mlx_image_t *img)
{
	int	distance;
	int	offset;

	distance = (img->width / 2) / (map->width + map->height);
	offset = (img->width - map->width) / 2;
	map->point[y][x].x = (x - y) * distance * cos(45 * PI / 360) + offset;
	map->point[y][x].y = (x + y) * distance * sin(45 * PI / 360) \
		- (map->point[y][x].z * 2) + offset;
}

int	get_coordinates(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			to_isometric(x, y, map, img);
			x++;
		}
		y++;
	}
	return (1);
}

int	get_color(t_map *map, char *str)
{
	char			**split;
	int				res;
	uint32_t		color;
	uint32_t		col_res;

	split = ft_split(str, ',');
	if (split == NULL || *split == NULL)
		return (-1);
	res = ft_atoi(split[0]);
	color = ft_atoi_base(split[1] + 2, 16);
	col_res = convert_rgba();
	ft_memcpy(&map->point[map->height][map->x].z, &res, sizeof(res));
	ft_memcpy(&map->point[map->height][map->x].color, &color, sizeof(color));
	split_free(split);
	return (1);
}