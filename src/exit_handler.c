/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:32:29 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/17 18:35:52 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_close_map(t_map *map)
{
	int	rows_i;

	if (map)
	{
		if (map->name)
			free(map->name);
		if (map->fd >= 0)
		{
			close(map->fd);
			map->fd = -1;
		}
		if (map->pts)
			free(map->pts);
		if (&map->matrix)
		{
			rows_i = (int)map->rows;
			// del if last row isn't NULL
			if (!map->matrix[rows_i] && rows_i > 0)
				rows_i--;
			// end del
			while (map->matrix[rows_i] && rows_i-- >= 0)
				free(map->matrix[rows_i]);
			free(map->matrix);
		}
		free(&map);
	}
}

static void	err_exit_toggle(char *err_msg)
{
	if (err_msg)
	{
		ft_putstr_fd("\n>>> ERROR <<<\n", STDOUT_FILENO);
		ft_putstr_fd(err_msg, STDOUT_FILENO);
		ft_putstr_fd("\n\nTry again:\n./fdf \"<map_name>.fdf\"\n\n",
			STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("\nFdF terminated gracefully.\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	err_free_exit(t_data *data, t_img *img, t_map *map, char *err_msg)
{
	if (data)
	{
		if (img)
		{
			mlx_destroy_image(data->mlx_ptr, img->img_ptr);
			free(img->img_pxls_ptr);
		}
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
		if (data->win_ptr)
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			free(data->win_ptr);
		}
		free(data);
	}
	free_close_map(map);
	err_exit_toggle(err_msg);
}

// considering using perror(), strerror() and STDERR_FILENO

// need clear_image?
// void	clear_image(t_image *img, int len)
// {
// 	if (!img || !img->addr)
// 		return ;
// 	ft_bzero(img->addr, WIN_H * len);
// }