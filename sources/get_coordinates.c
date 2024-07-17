/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:09:35 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/17 15:00:26 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	to_isometric(int x, int y, t_map *map, mlx_image_t *img)
{
	int	distance;
	int	offset;

	distance = (img->width / 2) / (map->width + map->height);
	offset = (img->width - map->width) / 2;
	map->point[y][x].x = (x - y) * distance * cos(65 * PI / 360) + offset;
	map->point[y][x].y = (x + y) * distance * sin(65 * PI / 360) \
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

int	fraction(double start, double end, double current)
{
	if (start != end)
		return ((current - start) / (end - start));
	return (0);
}

int	get_color(t_map *map, char *str)
{
	char			**split;
	char			*nl;
	char			*rgba;

	if (ft_strchr(str, ',') != 0)
	{
		split = ft_split(str, ',');
		if (split == NULL || *split == NULL)
			return (-1);
		map->point[map->height][map->x].z = ft_atoi(split[0]);
		if (ft_strchr(split[1], '\n') != 0)
		{
			nl = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
			rgba = ft_strjoin(nl, "ff");
			free(nl);
		}
		else
			rgba = ft_strjoin(split[1], "ff");
		map->point[map->height][map->x].color = ft_atoi_base(rgba + 2, 16);
		free(rgba);
		split_free(split);
		return (1);
	}
	map->point[map->height][map->x].color = ft_atoi_base(str, 16);
	return (1);
}

