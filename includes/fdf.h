/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:05:28 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/08/30 16:26:54 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define PI 3.141592653589793238462643383279502884197
# include <fcntl.h>
# include <math.h>
# include "MLX42.h"
# include "./libft/libft.h"

typedef struct s_point
{
	double			x;
	double			y;
	int				z;
	int				r;
	int				g;
	int				b;
	int				a;
	uint32_t		color;
}	t_point;

typedef struct s_map
{
	mlx_t			*window;
	mlx_image_t		*img;
	t_point			**point;
	t_point			**backup;
	int				width;
	int				height;
	bool			point_alloc;
	bool			backup_alloc;
	bool			isometric;
	bool			top;
	bool			front;
	bool			right;
	double			zoom;
	double			alpha;
	double			gamma;
	double			theta;
	int				max_z;
	int				min_z;
	int				x_trans;
	int				y_trans;
}	t_map;

typedef struct s_draw
{
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	double			fraction;
}	t_draw;

//map functions

int			read_map(t_map *map, int fd, char **arg);
int			get_backup(t_map *map);
int			get_coordinates(t_map *map);
int			create_map(t_map *map, char **split, int index);
void		set_scale(t_map *map);
void		find_min_coordinates(t_map *map, t_point *min);
void		find_max_coordinates(t_map *map, t_point *max);
void		scale_coordinates(t_map *map, double scale);
void		rotate_all(t_map *map);
void		inital_points(t_map *map);
void		center_map(t_map *map);
void		scale_z(t_map *map);
void		find_min_max_z(t_map *map);

//line drawing functions

void		draw_line(mlx_image_t *img, t_draw *line, t_point *start, \
				t_point *end);
t_draw		init_draw(int start_x, int start_y, int end_x, int end_y);
void		draw_background(t_map *map);
void		draw_map(t_map *map);
void		draw_area(t_map *map);

//color functions

void		convert_to_rgba(t_point *point);
double		fraction(double start, double end, double current);
uint32_t	calculate_color(t_point *start, t_point *end, t_draw *line);
int			get_color(t_map *map, char *str, int index);
char		*add_alpha(char *str);

//helper functions

void		split_free(char **arr);
int			determine_base(const char *str);
void		init_map(t_map *map);
void		free_map(t_map *map, int err);
void		free_gnl(int fd);
void		free_backup(t_map *map, int err);

//hooks

void		ft_hook(void *param);
void		draw_again(void *param);
void		resize(int32_t width, int32_t height, void *param);
void		hook_zoom(t_map *map);
void		hook_translate(t_map *map);
void		hook_rotate(t_map *map);
void		hook_projection(t_map *map);

#endif
