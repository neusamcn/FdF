/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:32:29 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 06:10:38 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_close_map(t_map *map)
{
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
		if (map->matrix)
			free(map->matrix);
		free(map);
	}
}

static void	err_exit_toggle(char *err_msg)
{
	if (err_msg)
	{
		ft_putstr_fd("\n>>> ERROR <<<\n", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_putstr_fd("\n\nTry again:\n./fdf \"<map_name>.fdf\"\n\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("\nFdF terminated gracefully.\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	err_free_exit(t_data *data, t_img *img, t_map *map, char *err_msg)
{
	if (data)
	{
		if (data->mlx_ptr)
		{
			if (img && img->img_ptr)
				mlx_destroy_image(data->mlx_ptr, img->img_ptr);
			if (data->win_ptr)
				mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
		free(data);
	}
	free_close_map(map);
	err_exit_toggle(err_msg);
}

void	free_splat(char **splat)
{
	size_t	i;

	if (!splat)
		return ;
	i = 0;
	while (splat[i])
	{
		free(splat[i]);
		i++;
	}
	free(splat);
}

// considering using perror(), strerror() and STDERR_FILENO

// need clear_image?
// void	clear_image(t_image *img, int len)
// {
// 	if (!img || !img->addr)
// 		return ;
// 	ft_bzero(img->addr, WIN_H * len);
// }