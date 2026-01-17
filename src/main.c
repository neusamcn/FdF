/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:28:24 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/17 00:17:22 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	button_press(int button, int x, int y, t_data *data)
{
	if (button == 3)
	{
		ft_printf("Right mouse button pressed at (%d, %d).\n", x, y);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (button == 1)
		ft_printf("Left mouse button pressed at (%d, %d).\n", x, y);
	return (EXIT_SUCCESS);
}

// static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	int		offset;
// 	char	*dst;

// 	offset = (y * data->img.line_len) + (x * (data->img.bits_per_pxl / 8));
// 	dst = data->img.img_pxls_ptr + offset;
// 	*(unsigned int *)dst = color;
// }

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = (y * img->line_len) + (x * (img->bits_per_pxl / 8));
	dst = img->img_pxls_ptr + offset;
	*(unsigned int *)dst = color;
}

static void	color_screen(t_data *data, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < WIN_HEIGHT)
	{
		x = 0;
		while (x++ < WIN_WIDTH)
			my_mlx_pixel_put(&data->img, x, y, color);
	}
}

static int	handle_keysym(int keysym, t_data *data)
{

	if (keysym == XK_r)
		color_screen(data, 0xff0000);
	else if (keysym == XK_g)
		color_screen(data, 0xff00);
	else if (keysym == XK_b)
		color_screen(data, 0xff);
	else if (keysym == XK_Escape)
	{
		ft_printf("\n%d key (ESC) was pressed.\n\n", keysym);
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		exit(EXIT_SUCCESS);
	}
	// push the READY image to window
	// the last parameters are the offset image-window
	ft_printf("The %d key has been pressed\n\n", keysym);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*map_name;

	if (ac == 2)
	{
		map_name = map_name_check(av[1]);
		if (!map_name)
		{
			free(map_name);
			ft_putstr_fd("\n>>> ERROR <<<\nInvalid map name.\n\n", 1);
			ft_putstr_fd("Try again:\n./fdf \"<map_name>.fdf\"\n\n", 1);
			exit(EXIT_FAILURE);
		}
		data.mlx = mlx_init();
		if (!data.mlx)
		{
			ft_putstr_fd("\n>>> ERROR <<<\nmlx coulnd't start.\n\n", 1);
			return (EXIT_FAILURE);
		}
		data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, map_name);
		if (!data.win)
		{
			ft_putstr_fd("\n>>> ERROR <<<\nwindow coulnd't open.\n\n", 1);
			mlx_destroy_display(data.mlx);
			free(data.mlx);
			return (EXIT_FAILURE);
		}

		// Code to create an image and get the related DATA
		data.img.img_ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
		if (!data.img.img_ptr)
		{
			ft_putstr_fd("\n>>> ERROR <<<\ncouln't create image.\n\n", 1);
			mlx_destroy_window(data.mlx, data.win);
			mlx_destroy_display(data.mlx);
			free(data.mlx);
			return (EXIT_FAILURE);
		}
		data.img.img_pxls_ptr = mlx_get_data_addr(data.img.img_ptr,
				&data.img.bits_per_pxl, &data.img.line_len, &data.img.endian);
		if (!data.img.img_pxls_ptr)
		{
			ft_putstr_fd("\n>>> ERROR <<<\ncouln't get data address.\n\n", 1);
			mlx_destroy_image(data.mlx, data.img.img_ptr);
			mlx_destroy_window(data.mlx, data.win);
			mlx_destroy_display(data.mlx);
			free(data.mlx);
			return (EXIT_FAILURE);
		}
		ft_printf("Line_len %d <-> WIN_WIDTH %d\nbpp %d\nendian %d\n",
			data.img.line_len, WIN_WIDTH, data.img.bits_per_pxl,
			data.img.endian);
		mlx_key_hook(data.win, handle_keysym, &data);
		mlx_hook(data.win, ButtonPress, ButtonPressMask, &button_press, &data);
		mlx_loop(data.mlx);
	}
	return (EXIT_SUCCESS);
}
/*
Int to isometric ?

err_free_exit(t_pointers *data, t_image *img, char *err_msg)
...
ft_putstr(ERROR);
ft_putstr(err_msg);
*/