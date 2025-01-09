/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 18:46:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->eat_count >= philo->data->meals_count
		&& philo->data->meals_count != -1)
	{
		philo->data->stop = 1;
		return ;
	}
	first_fork = philo->philo_num - 1;
	second_fork = philo->philo_num % philo->data->num_of_philos;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	print_action(get_current_time() - philo->data->start_time, philo->philo_num,
		TOOK_FORK);
	print_action(get_current_time() - philo->data->start_time, philo->philo_num,
		EAT);
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_mssleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	philo->next_state = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time();
	if (!philo->data->stop)
		print_action(time - philo->data->start_time, philo->philo_num, SLEEP);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_mssleep(philo->data->time_to_sleep);
	philo->next_state = THINK;
}

void	philo_think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time();
	if (!philo->data->stop)
		print_action(time - philo->data->start_time, philo->philo_num, THINK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->next_state = EAT;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->next_state != DEATH && !philo->data->stop)
	{
		if (philo->next_state == EAT && philo->data->num_of_philos > 1)
			philo_eat(philo);
		else if (philo->next_state == SLEEP)
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
