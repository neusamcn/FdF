/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:19:59 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 06:13:02 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	map_opt(t_map *map)
{
	size_t	cols_i;

	cols_i = 0;
	while (cols_i < map->cols)
	{
		map->matrix[cols_i] = map->pts + (cols_i * map->rows);
		cols_i++;
	}
	if (map->fd >= 0)
	{
		close(map->fd);
		map->fd = -1;
	}
}

static void	count_map_rows(t_map *map, char	*line)
{
	map->rows = 1;
	free(line);
	line = get_next_line(map->fd);
	while (line)
	{
		map->rows++;
		free(line);
		line = get_next_line(map->fd);
	}
}

static void	count_map_dims(t_map *map)
{
	char	*line;
	char	*trimmed_line;
	char	**cols_matrix;

	line = get_next_line(map->fd);
	if (!line)
		err_free_exit((t_data *)0, (t_img *)0, map, "Map file is empty.");
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
	{
		free(line);
		err_free_exit((t_data *)0, (t_img *)0, map, "Map file is empty.");
	}
	cols_matrix = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!cols_matrix)
	{
		free(line);
		err_free_exit((t_data *)0, (t_img *)0, map, "Map file is empty.");
	}
	map->cols = 0;
	while (cols_matrix[map->cols])
		map->cols++;
	free_splat(cols_matrix);
	count_map_rows(map, line);
}

static char	*map_name_check(char *map_name)
{
	char	*trimmed_name;
	char	*name_ext;

	trimmed_name = ft_strtrim(map_name, " \f\n\r\t\v");
	if (!trimmed_name)
		return (NULL);
	name_ext = ft_strrchr(trimmed_name, (int)('.'));
	if (name_ext && ft_strncmp(name_ext, ".fdf", 4) == 0)
		return (trimmed_name);
	return (NULL);
}

t_map	*map_init(char **av)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		err_free_exit((t_data *)0, (t_img *)0, map,
			"Memory allocation for map struct failed.");
	map->name = map_name_check(av[1]);
	if (!map->name)
		err_free_exit((t_data *)0, (t_img *)0, map, "Invalid map name.");
	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
	{
		perror("Error opening map file");
		err_free_exit((t_data *)0, (t_img *)0, map, "");
	}
	count_map_dims(map);
	map->pts = ft_calloc(map->cols * map->rows, sizeof(t_point));
	if (!map->pts)
		err_free_exit((t_data *)0, (t_img *)0, map, "Can't build map->pts.");
	map->matrix = ft_calloc(map->cols, sizeof(t_point *));
	if (!map->matrix)
		err_free_exit((t_data *)0, (t_img *)0, map, "Can't build map->matrix.");
	map_opt(map);
	return (map);
}
