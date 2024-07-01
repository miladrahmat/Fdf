/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:05:28 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/01 17:39:11 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"

typedef struct	s_map
{
	int			**memory;
	int			len_x;
	int			len_y;
	int			x;
	int			y;
	int			z;
}	t_map;

void	split_free(char **arr);
int		get_rgba(int r, int g, int b, int a);

#endif
