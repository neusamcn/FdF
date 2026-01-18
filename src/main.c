/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:28:24 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 05:36:10 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	hook_handler(t_data *data)
{
	err_free_exit(data, &data->img, data->map, NULL);
	return (EXIT_SUCCESS);
}

static int	handle_keysym(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_putstr_fd("\n(ESC) key was pressed.\n", STDOUT_FILENO);
		err_free_exit(data, &(data->img), data->map, NULL);
	}
	return (EXIT_SUCCESS);
}

static void	init_mlx_window(t_data *data, t_map *map)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		err_free_exit(data, &(data->img), map, "mlx couldn't start.");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, map->name);
	if (!data->win_ptr)
		err_free_exit(data, &(data->img), map, "mlx window couldn't open.");
}

static void	init_image(t_data *data, t_map *map)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (!data->img.img_ptr)
		err_free_exit(data, &(data->img), map, "couldn't create image.");
	data->img.img_pxls_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pxl, &data->img.line_len,
			&data->img.endian);
	if (!data->img.img_pxls_ptr)
		err_free_exit(data, &(data->img), map,
			"couldn't get data address.");
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*data;

	if (ac == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		map = map_init(av);
		map_parser(map);
		data->map = map;
		win_init(map, &data->win);
		init_mlx_window(data, map);
		init_image(data, map);
		img_render(data);
		mlx_key_hook(data->win_ptr, handle_keysym, data);
		mlx_hook(data->win_ptr, DestroyNotify, 0, hook_handler, data);
		mlx_loop(data->mlx_ptr);
		err_free_exit(data, &(data->img), map, NULL);
	}
	err_free_exit((t_data *)0, (t_img *)0, (t_map *)0,
		"Invalid amount of arguments.");
}
