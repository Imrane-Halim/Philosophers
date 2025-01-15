/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/15 10:47:05 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].th_id, NULL, routine, &data->philos[i]);
		usleep(100);
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].th_id, NULL);
		i++;
	}
}

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
	data = init_struct(ac, av);
	if (!data)
		return (write(STDERR_FILENO, "malloc error\n", 14), EXIT_FAILURE);
	if (data->num_of_philos < 1)
		return (clean_all(data), EXIT_SUCCESS);
	run_simulation(data);
	clean_all(data);
	return (0);
}
