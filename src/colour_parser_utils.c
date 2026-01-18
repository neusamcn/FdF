/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parser_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 04:34:19 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 05:05:04 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

int	ft_issign(int c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

char	*ft_str_tolower(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	check_base(char *input, char *base)
{
	size_t	i;

	i = 0;
	if (!input || input[0] == '\0')
		return (0);
	while (input[i])
	{
		if (!ft_strchr(base, input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	z_colour_check(char *input)
{
	size_t	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (ft_issign(input[i]) && ft_isdigit(input[i + 1]))
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i++]))
			return (0);
	}
	return (1);
}
