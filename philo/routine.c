/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/18 22:19:19 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_ctl(t_philo *philo, int first_fork, int second_fork, int lock)
{
	if (lock == FORKS_LOCK)
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
		return ;
	}
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
	forks_ctl(philo, first_fork, second_fork, FORKS_LOCK);
	pthread_mutex_lock(&philo->data->mutex);
	should_stop = philo->data->stop;
	if (!should_stop)
	{
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, "has taken a fork");
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, "is eating");
		philo->last_meal_time = get_current_time();
		philo->eat_count++;
	}
	pthread_mutex_unlock(&philo->data->mutex);
	ft_mssleep(philo->data->time_to_eat, philo->data);
	forks_ctl(philo, first_fork, second_fork, FORKS_UNLOCK);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, "is sleeping");
	pthread_mutex_unlock(&philo->data->mutex);
	ft_mssleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->stop)
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, "is thinking");
	pthread_mutex_unlock(&philo->data->mutex);
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
		if (philo->eat_count >= philo->data->meals_count
			&& philo->data->meals_count != -1)
			continue ;
		if (philo->data->num_of_philos <= 1)
			continue ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
