/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/15 10:47:13 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo, int first_fork, int second_fork)
{
	if (first_fork < second_fork)
	{
		pthread_mutex_lock(&philo->data->forks[first_fork]);
		pthread_mutex_lock(&philo->data->forks[second_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[second_fork]);
		pthread_mutex_lock(&philo->data->forks[first_fork]);
	}
}

void	unlock_forks(t_philo *philo, int first_fork, int second_fork)
{
	if (first_fork < second_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
	}
}

void	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	int	should_stop;

	first_fork = philo->philo_num - 1;
	second_fork = philo->philo_num % philo->data->num_of_philos;
	lock_forks(philo, first_fork, second_fork);
	pthread_mutex_lock(&philo->data->mutex);
	should_stop = philo->data->stop;
	if (!should_stop)
	{
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, TOOK_FORK);
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, EAT);
		philo->last_meal_time = get_current_time();
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->data->mutex);
	ft_mssleep(philo->data->time_to_eat);
	unlock_forks(philo, first_fork, second_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, SLEEP);
	pthread_mutex_unlock(&philo->data->mutex);
	ft_mssleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, THINK);
	pthread_mutex_unlock(&philo->data->mutex);
}
