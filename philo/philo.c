/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/03 18:07:27 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_philo_routine(t_philo *data)
{
	(void)data;
}
void	run_simulation(t_data *data)
{
	(void)data;
}

int	main(int ac, char **av)
{
	t_data	data;

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
	data = init_struct(ac, av);
	if (!data.philos)
		return (write(STDERR_FILENO, "malloc error\n", 14), EXIT_FAILURE);
	if (data.num_of_philos < 1)
		return (EXIT_SUCCESS);
	run_simulation(&data);
	return (0);
}
