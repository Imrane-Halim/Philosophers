/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/01 10:53:09 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac < 4 || ac > 5)
	{
		write(STDERR_FILENO,
			"usage: ./philo <N_PHILO> <DEATH_TIME>"
			" <EAT_TIME> [<N_EAT_TIMES>]\n",
			66);
		return (EXIT_FAILURE);
	}
	return (0);
}
