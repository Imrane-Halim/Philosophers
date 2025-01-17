/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:28:32 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/10 10:39:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	res;
	int	sign;

	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	res = 0;
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		if (res < 0)
			return (-1);
		s++;
	}
	return (res * sign);
}

static int	is_valid_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_range(char *s)
{
	int	n;

	n = ft_atoi(s);
	return (n >= 0 && n <= INT_MAX);
}

int	are_valid_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_num(av[i]))
		{
			write(STDERR_FILENO,
				"INVALID NUMBER WAS PASSED\n", 27);
			return (0);
		}
		if (!is_valid_range(av[i]))
		{
			write(STDERR_FILENO,
				"NUMBER NOT WTHIN RANGE: [0..INT_MAX]\n", 38);
			return (0);
		}
		i++;
	}
	return (1);
}
