/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:27:39 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/02 15:41:20 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_philo_routine(t_data *data)
{
	(void)data;
}
void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	
	while (i < data->num_of_philos)
	{
		run_philo_routine(data);
		i++;
	}
}

t_data	init_struct(int ac, char **av)
{
	t_data	data;
	int		i;
	data.num_of_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.times_to_eat = ft_atoi(av[5]);
	else
		data.times_to_eat = -1;
	data.philos = malloc(sizeof(t_philo) * data.num_of_philos);
	if (data.philos)
	{
		i = 0;
		while (i < data.num_of_philos)
		{
			data.philos[i].eat_times = 0;
			data.philos[i].is_dead = 0;
			data.philos[i].n_forks = 1;
			data.philos[i].philo_num = i + 1;
			i++;
		}
	}
	gettimeofday(&data.timestamp_start, NULL);
	return (data);
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
