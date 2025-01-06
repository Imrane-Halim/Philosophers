/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:47 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/06 20:08:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_struct(int ac, char **av)
{
	t_data	data;
	int		i;

	data.num_of_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.time_to_eat = (ac == 6) * ft_atoi(av[5]) + (ac != 6) * -1;
	data.philos = malloc(sizeof(t_philo) * data.num_of_philos);
	if (data.philos)
	{
		i = 0;
		while (i < data.num_of_philos)
		{
			data.philos[i].eat_count = 0;
			data.philos[i].state = THINK;
			data.philos[i].philo_num = i + 1;
			data.philos[i].last_meal_time = 0;
			pthread_mutex_init(&data.philos[i].mutex_fork, NULL);
			i++;
		}
	}
	data.time_elapsed = 0;
	return (data);
}

void	print_action(int time, int philo_num, enum e_state action)
{
	printf("%d\t%d ", time, philo_num + 1);
	if (action == TOOK_FORK)
		printf("has taken a fork\n");
	else if (action == DEATH)
		printf("died\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
}
