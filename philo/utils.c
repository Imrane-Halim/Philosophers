/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:47 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/15 10:12:58 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mssleep(long long sleep_time)
{
	long long	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
		usleep(100);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].philo_num = i + 1;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].n_forks = 1;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

t_data	*init_struct(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_count = ft_atoi(av[5]);
	else
		data->meals_count = -1;
	data->start_time = get_current_time();
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (free(data), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (free(data->philos), free(data), NULL);
	data->stop = 0;
	init_philos(data);
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->mutex);
	free(data->forks);
	free(data->philos);
	free(data);
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
