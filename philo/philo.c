/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/01 18:02:39 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_simulation(t_data *data)
{
	(void)data;
}

t_data	init_struct(int ac, char **av)
{
	t_data	data;
	
	data.num_of_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.times_to_eat = ft_atoi(av[5]);
	else
		data.times_to_eat = -1;
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		write(STDERR_FILENO,
			"usage: ./philo <N_PHILO> <DEATH_TIME>"
			" <EAT_TIME> <SLEEP_TIME>[<N_EAT_TIMES>]\n",
			78);
		return (EXIT_FAILURE);
	}
	if (!are_valid_args(ac, av))
		return (EXIT_FAILURE);
	data = init_struct(ac, av);
	if (data.num_of_philos < 1)
		return (EXIT_SUCCESS);
	run_simulation(&data);
	return (0);
}
