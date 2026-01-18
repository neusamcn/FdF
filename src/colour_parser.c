/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 03:57:29 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 05:04:50 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	parse_colour(t_map *map, char *colour, size_t x, size_t y)
{
	char	*trim;
	int		dec;
	size_t	size;

	ft_str_tolower(colour);
	if (ft_strncmp(colour, "0x", 2) != 0)
		return (0);
	size = ft_strlen(colour) - 2;
	trim = ft_calloc(size + 1, sizeof(char));
	if (!trim)
		return (-1);
	ft_strlcpy(trim, colour + 2, size + 1);
	if (!check_base(trim, "0123456789abcdef"))
	{
		free(trim);
		return (0);
	}
	dec = ft_atoi_base(trim, 16);
	map->matrix[x][y].colour = dec;
	free(trim);
	return (1);
}

static char	*extract_colour(char **temp)
{
	char	*colour;

	if (temp[1] && ft_strlen(temp[1]) > 0)
		colour = ft_strdup(temp[1]);
	else
		colour = ft_strdup("0xFFFFFF");
	return (colour);
}

static char	*handle_split_point(char *point, char **z_colour, char **colour)
{
	char	**temp;

	temp = ft_split(point, ',');
	if (!temp || !temp[0])
	{
		free_splat(temp);
		return (NULL);
	}
	*z_colour = ft_strdup(temp[0]);
	*colour = extract_colour(temp);
	free_splat(temp);
	if (!*z_colour || !*colour)
	{
		free(*z_colour);
		free(*colour);
		return (NULL);
	}
	return (*z_colour);
}

static char	*handle_simple_point(char *point, char **colour)
{
	char	*z_colour;

	z_colour = ft_strdup(point);
	*colour = ft_strdup("0xFFFFFF");
	if (!z_colour || !*colour)
	{
		free(z_colour);
		free(*colour);
		return (NULL);
	}
	return (z_colour);
}

char	*set_colour(t_map *map, char *point, size_t x, size_t y)
{
	char	*colour;
	char	*z_colour;

	colour = NULL;
	z_colour = NULL;
	if (ft_strchr(point, ','))
		z_colour = handle_split_point(point, &z_colour, &colour);
	else
		z_colour = handle_simple_point(point, &colour);
	if (!z_colour || !colour)
		return (NULL);
	if (!parse_colour(map, colour, x, y))
	{
		free(colour);
		free(z_colour);
		return (NULL);
	}
	free(colour);
	return (z_colour);
}
