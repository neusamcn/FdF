/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:28:12 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 06:12:57 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	parse_points(t_map *map, long x, long y, long z)
{
	t_point	*point;
	size_t	width;
	size_t	height;

	point = &map->matrix[x][y];
	width = map->cols - 1;
	height = map->rows - 1;
	point->x = x;
	point->y = y;
	point->z = z;
	point->c_x = (double)x - (double)width / 2.0;
	point->c_y = (double)y - (double)height / 2.0;
	point->iso_x = (point->c_x - point->c_y) * cos(M_PI / 6);
	point->iso_y = (point->c_x + point->c_y) * sin(M_PI / 6) - (double)point->z;
}

static long	extract_z_value(t_map *map, char *point_str, size_t x, size_t y)
{
	char	*z_colour;
	long	z;

	z_colour = set_colour(map, point_str, x, y);
	if (!z_colour || !z_colour_check(z_colour))
	{
		map->matrix[x][y].colour = 0xFFFFFF;
		if (z_colour)
			free(z_colour);
		z = ft_atol(point_str);
	}
	else
	{
		z = ft_atol(z_colour);
		free(z_colour);
	}
	return (z);
}

static void	z_parser(t_map *map, char **line_matrix, size_t y)
{
	size_t	x;
	long	z;

	x = 0;
	while (line_matrix[x] && x < map->cols)
	{
		z = extract_z_value(map, line_matrix[x], x, y);
		if (z < INT_MIN || z > INT_MAX)
		{
			free_splat(line_matrix);
			err_free_exit((t_data *)0, (t_img *)0, map,
				"Found z that is not an int; cannot build map.");
		}
		parse_points(map, x, y, z);
		x++;
	}
}

static void	map_row_parser(t_map *map, char *line, size_t row_y)
{
	char	*trimmed_line;
	char	**line_matrix;

	trimmed_line = ft_strtrim(line, "\n");
	line_matrix = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	z_parser(map, line_matrix, row_y);
	free_splat(line_matrix);
}

void	map_parser(t_map *map)
{
	char	*line;
	size_t	row;

	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
	{
		perror("Error opening map file");
		err_free_exit((t_data *)0, (t_img *)0, map, "");
	}
	row = 0;
	while (row < map->rows)
	{
		line = get_next_line(map->fd);
		if (!line)
			err_free_exit((t_data *)0, (t_img *)0, map, NULL);
		map_row_parser(map, line, row);
		free(line);
		row++;
	}
	if (map->fd >= 0)
	{
		close(map->fd);
		map->fd = -1;
	}
}
