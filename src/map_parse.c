/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:19:59 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/16 22:34:16 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	*map_name_check(char *map_name)
{
	char	*trimmed_name;
	char	*name_ext;

	trimmed_name = ft_strtrim(map_name, " \f\n\r\t\v");
	if (!trimmed_name)
		return (NULL);
	name_ext = ft_strrchr(trimmed_name, (int)('.'));
	if (name_ext && ft_strncmp(name_ext, ".fdf", 4) == 0)
		return (trimmed_name);
		// free trimmed_name later
	return (NULL);
}

// void	get_dims(t_map	*map, int fd)
// {
// 	char	*line;
// 	size_t	cols;

// 	line = get_next_line(fd);
// 	cols = get_cols(line);
// 	if (!cols)
// 		return ;
// 	map->rows++;
// 	map->cols = cols;
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		if (!line)
// 			return ;
// 		map->rows++;
// 	}
// 	free(line);
// }

// t_map	*open_map(char *map_name)
// {
// 	int		fd;
// 	t_map	*map;
// 	size_t	i;

// 	fd = open(map_name, O_RDONLY);
// 	map = ft_calloc(1, sizeof(t_map));
// 	if (!map || fd < 0)
// 		return (NULL);
// 	i = 0;
// 	map->rows = 0;
// 	map->cols = 0;
// 	get_dims(map, fd);
// 	map->pts = ft_calloc(map->cols * map->rows, sizeof(t_point));
// 	map->points = ft_calloc(map->cols, sizeof(t_point *));
// 	if (!map->points)
// 	{
// 		free_map(map);
// 		close(fd);
// 		return (NULL);
// 	}
// 	while (i++ < map->cols)
// 		map->points[i] = map->pts + (i * map->rows);
// 	close(fd);
// 	return (map);
// }
