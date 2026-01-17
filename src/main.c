/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:28:24 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/17 16:20:19 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	btn_press(int button, int x, int y, t_data *data)
{
	if (button == 3)
	{
		ft_printf("Right mouse button pressed at (%d, %d).\n", x, y);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
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
	while (y++ < WIN_H)
	{
		x = 0;
		while (x++ < WIN_W)
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
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		mlx_destroy_display(data->mlx_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	// push the READY image to window
	// the last parameters are the offset image-window
	ft_printf("The %d key has been pressed\n\n", keysym);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	*map;

	if (ac == 2)
	{
		map_init(av);
		data->mlx_ptr = mlx_init();
		if (!data->mlx_ptr)
			err_free_exit(data, &(data->img), map, "mlx couldn't start.");
		data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, map->name);
		if (!data->win_ptr)
			err_free_exit(data, &(data->img), map, "mlx window couldn't open.");
		// Code to create an image and get the related DATA
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
		if (!data->img.img_ptr)
			err_free_exit(data, &(data->img), map, "couldn't create image.");
		data->img.img_pxls_ptr = mlx_get_data_addr(data->img.img_ptr,
				&data->img.bits_per_pxl, &data->img.line_len,
				&data->img.endian);
		if (!data->img.img_pxls_ptr)
			err_free_exit(data, &(data->img), map,
				"couldn't get data address.");
		// TESTER START
		ft_printf("Line_len %d <-> WIN_W %d\nbpp %d\nendian %d\n",
			data->img.line_len, WIN_W, data->img.bits_per_pxl,
			data->img.endian);
		// TESTER END
		mlx_key_hook(data->win_ptr, handle_keysym, &data);
		mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask, &btn_press,
			&data);
		mlx_loop(data->mlx_ptr);
		err_free_exit(data, &(data->img), map, "");
	}
	err_free_exit(data, &(data->img), map, "Invalid amount of arguments.");
}

/*
Int to isometric ?

*/