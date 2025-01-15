/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/15 11:09:24 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	return (get_time_elapsed(philo->last_meal_time) > philo->data->time_to_die);
}

void	monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		if (check_death(&data->philos[i]))
		{
			data->stop = 1;
			print_action(get_time_elapsed(data->start_time),
				data->philos[i].philo_num, "died");
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		pthread_mutex_unlock(&data->mutex);
		i = (i + 1) % data->num_of_philos;
		usleep(100);
	}
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_time_elapsed(long long time)
{
	return (get_current_time() - time);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (check_death(philo) || philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex);
		if (philo->data->num_of_philos > 1)
		{
			if (philo->eat_count >= philo->data->meals_count
				&& philo->data->meals_count != -1)
				return (philo->data->stop = 1, NULL);
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
	}
	return (NULL);
}
