/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/01 16:00:37 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 4 || ac > 5)
	{
		write(STDERR_FILENO,
			"usage: ./philo <N_PHILO> <DEATH_TIME>"
			" <EAT_TIME> [<N_EAT_TIMES>]\n",
			66);
		return (EXIT_FAILURE);
	}
	if (!are_valid_args(ac, av))
		return (EXIT_FAILURE);
	data.num_of_philos = ft_atoi(av[1]);
	if (data.num_of_philos < 1)
		return (EXIT_SUCCESS);
	return (0);
}
