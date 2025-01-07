/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 18:04:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	long long	current_time;
	
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->eat_count >= philo->data->meals_count
		&& philo->data->meals_count != -1)
	{
		philo->data->stop = 1;
		return ;
	}
	current_time = get_current_time();
	philo->last_meal_time = current_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	print_action(current_time - philo->data->start_time, philo->philo_num,
		TOOK_FORK);
	print_action(current_time - philo->data->start_time, philo->philo_num, EAT);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->next_state = SLEEP;
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork_mutex);
}

void	philo_sleep(t_philo *philo)
{
	long long	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	print_action(time - philo->data->start_time, philo->philo_num, SLEEP);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->next_state = THINK;
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	long long	time;

	time = get_current_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	print_action(time - philo->data->start_time, philo->philo_num, THINK);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->next_state = EAT;
	usleep(5 * 1000);
}

int	check_death(t_philo *philo)
{
	if (get_time_elapsed(philo->last_meal_time) >= philo->data->time_to_die)
	{
		philo->data->stop = 1;
		philo->next_state = DEATH;
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->stop != 1)
	{
		if (check_death(philo))
			break ;
		if (philo->next_state == EAT)
			philo_eat(philo);
		else if (philo->next_state == SLEEP)
			philo_sleep(philo);
		else if (philo->next_state == THINK)
			philo_think(philo);
	}
	if (philo->next_state == DEATH)
		print_action(get_time_elapsed(philo->data->start_time),
			philo->philo_num, DEATH);
	return (NULL);
}

void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (i % 2 == 0)
			data->philos[i].next_state = EAT;
		pthread_create(&data->philos[i].th_id, NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].th_id, NULL);
		i++;
	}
}
