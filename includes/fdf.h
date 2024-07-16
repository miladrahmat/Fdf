/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:05:28 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/16 18:49:33 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define PI 3.141592653589793238462643383279502884197
# include <fcntl.h>
# include <math.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include "./libft/vector.h"

typedef struct s_point
{
	double			x;
	double			y;
	int				z;
	t_vec			rgba;
	uint32_t		color;
}	t_point;

typedef struct s_map
{
	t_point		**point;
	int			width;
	int			height;
	int			x;
	int			y;
	bool		point_alloc;
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

//map functions

int		read_map(t_map *map, int fd, char **arg);
int		get_coordinates(mlx_image_t *img, t_map *map);
int		create_map(t_map *map, char **split);
void	init_map(t_map *map);
void	free_map(t_map *map);
int		get_color(t_map *map, char *str);

//line drawing functions

void	draw_line(mlx_image_t *img, t_draw *line, uint32_t color);
t_draw	init_draw(int start_x, int start_y, int end_x, int end_y);
void	draw_map(mlx_image_t *img, t_map *map);
void	draw_area(mlx_image_t *img, t_map *map);

//helper functions

void	split_free(char **arr);
int		get_rgba(int r, int g, int b, int a);
void	ft_hook(void *param);

#endif
