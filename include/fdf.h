/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:42:14 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/16 23:50:02 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pxls_ptr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	long	x;
	long	y;
	long	z;
	double	c_x;
	double	c_y;
	double	iso_x;
	double	iso_y;
	long	screen_x;
	long	screen_y;
	int		colour;
}	t_point;

typedef struct s_map
{
	size_t	rows;
	size_t	cols;
	t_point	*pts;
	t_point	**points;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;


char	*map_name_check(char *map_name);
// t_map	*open_map(char *map_name);
// void	get_dims(t_map	*map, int fd);

#endif