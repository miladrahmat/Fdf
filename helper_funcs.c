/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:54:17 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/03 14:26:11 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_map(t_map *map, bool check)
{
	int	i;

	i = 0;
	if (check == true)
	{
		while (i < map->len_y)
		{
			free(map->memory[i]);
			i++;
		}
	}
	free(map->memory);
	map->len_x = 0;
	map->len_y = 0;
	map->x = 0;
	map->y = 0;
	map->z = 0;
}

int	get_size(int fd, char **arg)
{
	char	buf;
	int		count;
	ssize_t	check;

	count = 0;
	buf = '0';
	check = 1;
	while (check > 0)
	{
		check = read(fd, &buf, sizeof(buf));
		if (check == -1)
			return (-1);
		if (buf == '\n' || buf == '\0')
			count++;
	}
	close(fd);
	fd = open(arg[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	else
		return (count);
}
