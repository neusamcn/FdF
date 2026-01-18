/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 04:26:13 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 04:30:21 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	is_valid_char(char c, int base)
{
	if (base < 1 || base > 16)
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	if (base > 10 && ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))
		return (1);
	return (0);
}

static int	char_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

static int	validate_string(const char *str, int base)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!is_valid_char(str[i], base))
			return (0);
		i++;
	}
	return (1);
}

static int	convert_to_decimal(const char *str, int base, int start_idx)
{
	int	result;
	int	digit;

	result = 0;
	while (str[start_idx])
	{
		digit = char_to_digit(str[start_idx]);
		if (digit >= base)
			return (0);
		result = result * base + digit;
		start_idx++;
	}
	return (result);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	start_idx;
	int	result;

	if (!validate_string(str, str_base))
		return (0);
	sign = 1;
	start_idx = 0;
	if (str[0] == '-')
	{
		sign = -1;
		start_idx = 1;
	}
	result = convert_to_decimal(str, str_base, start_idx);
	return (result * sign);
}
