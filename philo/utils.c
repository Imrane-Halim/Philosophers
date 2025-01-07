/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:47 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/07 16:53:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_struct(int ac, char **av)
{
	static t_data	data;
	int		i;

	data.num_of_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.meals_count = ft_atoi(av[5]);
	else
		data.meals_count = -1;
	data.start_time = get_current_time();
	data.philos = malloc(sizeof(t_philo) * data.num_of_philos);
	if (data.philos)
	{
		i = 0;
		while (i < data.num_of_philos)
		{
			data.philos[i].eat_count = 0;
			data.philos[i].next_state = THINK;
			data.philos[i].philo_num = i + 1;
			data.philos[i].last_meal_time = data.start_time;
			data.philos[i].data = &data;
			pthread_mutex_init(&data.philos[i].fork_mutex, NULL);
			i++;
		}
	}
	data.stop = 0;
	pthread_mutex_init(&data.print_mutex, NULL);
	return (data);
}

void	print_action(int time, int philo_num, enum e_state action)
{
	printf("%d\t%d ", time, philo_num);
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

void	monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos && !data->stop)
	{
		i = (i + 1) % data->num_of_philos;
	}
	if (data->philos[i].next_state == DEATH)
		print_action(data->start_time, i, DEATH);
	else
		printf("the number of allowed meals was reached\n");
}

long long get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long get_time_elapsed(long long time)
{
	return (get_current_time() - time);
}
