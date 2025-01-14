/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/14 19:55:58 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->philo_num - 1;
	second_fork = philo->philo_num % philo->data->num_of_philos;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->mutex);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		TOOK_FORK);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		EAT);
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->mutex);
	ft_mssleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	philo->next_state = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
			SLEEP);
	pthread_mutex_unlock(&philo->data->mutex);
	philo->next_state = THINK;
	ft_mssleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
			THINK);
	philo->next_state = EAT;
	pthread_mutex_unlock(&philo->data->mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->next_state == DEATH || philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex);
		if (philo->next_state == EAT && philo->data->num_of_philos > 1)
		{
			if (philo->eat_count >= philo->data->meals_count
				&& philo->data->meals_count != -1)
			{
				philo->data->stop = 1;
				break ;
			}
			philo_eat(philo);
		}
		if (philo->next_state == SLEEP)
			philo_sleep(philo);
		else if (philo->next_state == THINK)
			philo_think(philo);
	}
	return (NULL);
}

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
