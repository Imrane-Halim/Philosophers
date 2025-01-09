/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 11:31:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mssleep(t_philo *philo, long long sleep_time)
{
	long long	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
	{
		if (check_death(philo))
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	long long	current_time;
	int			next_philo_idx;

	next_philo_idx = (philo->philo_num + 1) % philo->data->num_of_philos - 1;
	if ((philo->eat_count >= philo->data->meals_count
		&& philo->data->meals_count != -1))
	{
		philo->data->stop = 1;
		return ;
	}
	if (philo->data->num_of_philos <= 1)
		return ;
	pthread_mutex_lock(&philo->fork_mutex);

	philo->data->philos[next_philo_idx].n_forks--;
	philo->n_forks++;
	current_time = get_current_time();
	philo->last_meal_time = current_time;
	
	pthread_mutex_lock(&philo->data->print_mutex);
	print_action(current_time - philo->data->start_time, philo->philo_num, TOOK_FORK);
	print_action(current_time - philo->data->start_time, philo->philo_num, EAT);
	pthread_mutex_unlock(&philo->data->print_mutex);
	
	philo->eat_count++;
	philo->data->philos[next_philo_idx].n_forks++;
	philo->n_forks--;
	ft_mssleep(philo, philo->data->time_to_eat);
	
	pthread_mutex_unlock(&philo->fork_mutex);
	philo->next_state = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time();
	print_action(time - philo->data->start_time, philo->philo_num, SLEEP);
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_mssleep(philo, philo->data->time_to_sleep);
	philo->next_state = THINK;
}

void	philo_think(t_philo *philo)
{
	long long	time;
	
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_current_time();
	print_action(time - philo->data->start_time, philo->philo_num, THINK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->next_state = EAT;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		if (philo->next_state == EAT)
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
