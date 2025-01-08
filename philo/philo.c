/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/08 17:19:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		write(STDERR_FILENO,
			"usage: ./philo <N_PHILO> <DEATH_TIME>"
			" <EAT_TIME> <SLEEP_TIME> [<N_EAT_TIMES>]\n",
			79);
		return (EXIT_FAILURE);
	}
	if (!are_valid_args(ac, av))
		return (EXIT_FAILURE);
	if (ft_atoi(av[1]) == 0)
	{
		write(STDERR_FILENO,
			"You need at least 1 philosopher in the table!\n", 47);
		return (EXIT_FAILURE);
	}
	data = init_struct(ac, av);
	if (!data->philos)
		return (write(STDERR_FILENO, "malloc error\n", 14), EXIT_FAILURE);
	if (data->num_of_philos < 1)
		return (EXIT_SUCCESS);
	run_simulation(data);
	return (0);
}
