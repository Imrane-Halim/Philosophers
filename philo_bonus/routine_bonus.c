/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/17 14:51:52 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_data *data, t_philo *philo)
{
	sem_t	*print;
	sem_t	*forks;
	sem_t	*death;

	print = sem_open("print_sem", 0);
	forks = sem_open("forks_sem", 0);
	death = sem_open("death_sem", 0);
	sem_wait(forks);
	sem_wait(forks);
	sem_wait(print);
	print_action(get_time_elapsed(data->start_time), philo->philo_num,
		"has taken a fork");
	print_action(get_time_elapsed(data->start_time), philo->philo_num,
		"is eating");
	sem_wait(death);
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	sem_post(death);
	sem_post(print);
	ft_mssleep(data->time_to_eat);
	sem_post(forks);
	sem_post(forks);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	sem_t	*print;

	print = sem_open("print_sem", 0);
	sem_wait(print);
	print_action(get_time_elapsed(data->start_time), philo->philo_num,
		"is sleeping");
	sem_post(print);
	ft_mssleep(data->time_to_sleep);
}

void	philo_think(t_data *data, t_philo *philo)
{
	sem_t	*print;

	print = sem_open("print_sem", 0);
	sem_wait(print);
	print_action(get_time_elapsed(data->start_time), philo->philo_num,
		"is thinking");
	sem_post(print);
}

void	routine(t_data *data, t_philo *philo)
{
	pthread_t	th_monitor;
	t_monitor	monitor;
	sem_t		*death;

	monitor.data = data;
	monitor.philo = philo;
	monitor.stop = 0;
	death = sem_open("death_sem", 0);
	if (pthread_create(&th_monitor, NULL, monitoring, (void *)(&monitor)) != 0)
		exit(1);
	pthread_detach(th_monitor);
	while (1)
	{
		sem_wait(death);
		if (monitor.stop)
		{
			sem_post(death);
			return ;
		}
		sem_post(death);
		philo_eat(data, philo);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
}

void	run_simulation(t_data *data)
{
	int		i;
	pid_t	dead_pid;

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
	dead_pid = waitpid(-1, NULL, 0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].pid != dead_pid)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}
