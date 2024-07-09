/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- < mrahmat-@student.hive.fi >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:05:28 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/09 14:09:36 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <math.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"

typedef struct s_map
{
	int			**memory;
	int			len_x;
	int			len_y;
	int			x;
	int			y;
	int			z;
}	t_map;

typedef struct s_draw
{
	int	pixels;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}	t_draw;

void	split_free(char **arr);
int		get_rgba(int r, int g, int b, int a);
void	free_map(t_map *map, bool check);
int		get_size(int fd, char **arg);
int		read_map(t_map *map, int fd, char **arg);
int		create_map(t_map *map, char **split);
void	ft_hook(void *param);
int		ft_sqrt(int x, int y);
void	draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, uint32_t color);
t_draw	init_draw(int start_x, int start_y, int end_x, int end_y);
void	draw_map(mlx_image_t *img, t_map *map);
void	draw_area(mlx_image_t *img, t_map *map);
int		absolute(int nbr);

#endif
