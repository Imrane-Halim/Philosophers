/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/19 15:03:42 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_data *data, t_philo *philo)
{
	sem_wait(data->forks_sem);
	sem_wait(data->forks_sem);
	print_action(get_time_elapsed(data->start_time),
		philo->philo_num, "has taken a fork");
	print_action(get_time_elapsed(data->start_time),
		philo->philo_num, "is eating");
	sem_wait(data->death_sem);
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	sem_post(data->death_sem);
	ft_mssleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_action(get_time_elapsed(data->start_time),
		philo->philo_num, "is sleeping");
	ft_mssleep(data->time_to_sleep);
}

void	philo_think(t_data *data, t_philo *philo)
{
	print_action(get_time_elapsed(data->start_time),
		philo->philo_num, "is thinking");
}

void	routine(t_data *data, t_philo *philo)
{
	pthread_t	th_monitor;
	t_monitor	monitor;

	monitor.data = data;
	monitor.philo = philo;
	if (pthread_create(&th_monitor, NULL, monitoring, (void *)(&monitor)) != 0)
		exit(1);
	pthread_detach(th_monitor);
	while (1)
	{
		if (data->num_of_philos <= 1)
			continue ;
		if (data->meals_count == philo->eat_count && data->meals_count != -1)
		{
			sem_post(data->full_flag);
			break ;
		}
		if (philo->philo_num % 2 == 0)
			usleep(100);
		philo_eat(data, philo);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
}

void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(data, &data->philos[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	while (data->death_sem->__align != 99
		&& data->full_flag->__align != data->num_of_philos + 1)
		;
	ft_mssleep(50);
	i = 0;
	while (i < data->num_of_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}
