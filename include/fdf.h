/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:42:14 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 06:14:07 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _XOPEN_SOURCE

# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include <errno.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define WIN_W 1280
# define WIN_H 960

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pxls_ptr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_line
{
	long	x0;
	long	x1;
	long	y0;
	long	y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}	t_line;

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

typedef struct s_win
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	double	map_w;
	double	map_h;
	double	scale_x;
	double	scale_y;
	double	scale;
	double	offset_x;
	double	offset_y;
}	t_win;

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
	t_win	win;
	t_map	*map;
}	t_data;

void	err_free_exit(t_data *data, t_img *img, t_map *map, char *err_msg);
void	free_splat(char **splat);

t_map	*map_init(char **av);
void	map_parser(t_map *map);
char	*set_colour(t_map *map, char *point, size_t x, size_t y);
void	win_init(t_map *map, t_win *win);
void	img_render(t_data *data);

int		ft_atoi_base(const char *str, int str_base);
long	ft_atol(const char *nptr);
int		ft_isspace(int c);
int		ft_issign(int c);
char	*ft_str_tolower(char *str);
int		check_base(char *input, char *base);
int		z_colour_check(char *input);

#endif