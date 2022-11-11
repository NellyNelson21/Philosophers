/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:08:56 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 13:11:26 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_spaces(const char *s)
{
	if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n' || *s == '\v'
		|| *s == '\f')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (ft_spaces(str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	process_arg(char *arg)
{	
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!is_digit(arg[i]))
			return (0);
		i++;
	}
	return (ft_atoi(arg));
}
