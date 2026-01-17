/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:42:14 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/17 18:02:24 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define WIN_W 800
# define WIN_H 800

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
	char	*name;
	int		fd;
	size_t	rows;
	size_t	cols;
	t_point	*pts;
	t_point	**matrix;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;


void	err_free_exit(t_data *data, t_img *img, t_map *map, char *err_msg);
void	map_init(char **av);

#endif