/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmat- <mrahmat-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:00:16 by mrahmat-          #+#    #+#             */
/*   Updated: 2024/07/17 11:59:23 by mrahmat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*determine_base(const char *str, int base)
{
	int	i;

	i = 0;
	if (base == 16)
	{
		while (str[i] != '\0')
		{
			if (str[i] >= 'A' && str[i] <= 'F')
				return (HEX_UPPER_BASE);
			else if (str[i] >= 'a' && str[i] <= 'f')
				return (HEX_LOWER_BASE);
			else if (str[i] >= '0' && str[i] <= '9' && str[i + 1] == '\0')
				return (HEX_LOWER_BASE);
			i++;
		}
	}
	else if (base == 8)
		return (OCTAL_BASE);
	else if (base == 2)
		return (BINARY_BASE);
	return (0);
}

static int	ft_converter(const char *str, int base, int sign)
{
	int		nbr;
	int		s_i;
	int		b_i;
	char	*base_elems;

	s_i = 0;
	nbr = 0;
	base_elems = determine_base(str, base);
	if (base_elems == 0)
		return (0);
	while (str[s_i] != '\0')
	{
		nbr *= base;
		b_i = 0;
		while (str[s_i] != base_elems[b_i] && base_elems[b_i] != '\0')
			b_i++;
		if (base_elems[b_i] == '\0')
			return (0);
		nbr += b_i;
		s_i++;
	}
	return (nbr * sign);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	check;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = res * 10 + str[i++] - '0';
		if (res != check / 10 && sign == 1)
			return (-1);
		if (res != check / 10 && sign == -1)
			return (0);
		res = check;
	}
	return ((int)res * sign);
}

long	ft_atol(const char *str)
{
	long	nbr;
	long	sign;
	long	i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	ft_atoi_base(const char *str, int base)
{
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	return (ft_converter(&str[i], base, sign));
}
