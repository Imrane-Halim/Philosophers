/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 09:33:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex_fork);
    
    long long current_time = get_current_time();
	
    philo->last_meal_time = current_time;
    print_action(current_time - philo->data->start_time, philo->philo_num, TOOK_FORK);
    print_action(current_time - philo->data->start_time, philo->philo_num, EAT);
    philo->next_state = SLEEP;
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_philo *philo)
{
	long long time;

	time = get_current_time();
	print_action(time - philo->data->start_time, philo->philo_num, SLEEP);
	philo->next_state = THINK;
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	long long time;

	time = get_current_time();
	print_action(time - philo->data->start_time, philo->philo_num, THINK);
	philo->next_state = EAT;
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->next_state != DEATH || philo->data->stop != 1)
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
	data->philos[0].next_state = EAT;
	while (i < data->num_of_philos)
	{
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