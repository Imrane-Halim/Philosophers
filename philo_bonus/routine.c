/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/12 12:08:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->philo_num - 1;
	second_fork = philo->philo_num % philo->data->num_of_philos;
	philo->data->forks[first_fork] = sem_open("fork_sem", 0);
	philo->data->forks[second_fork] = sem_open("fork_sem", 0);
	philo->data->print_sem = sem_open("print_sem", 0);
	sem_wait(philo->data->forks[first_fork]);
	sem_wait(philo->data->forks[second_fork]);
	sem_wait(philo->data->print_sem);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		TOOK_FORK);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		EAT);
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	sem_post(philo->data->print_sem);
	ft_mssleep(philo->data->time_to_eat);
	sem_post(philo->data->forks[second_fork]);
	sem_post(philo->data->forks[first_fork]);
	philo->next_state = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	philo->data->print_sem = sem_open("print_sem", 0);
	sem_wait(philo->data->print_sem);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		SLEEP);
	sem_post(philo->data->print_sem);
	ft_mssleep(philo->data->time_to_sleep);
	philo->next_state = THINK;
}

void	philo_think(t_philo *philo)
{
	philo->data->print_sem = sem_open("print_sem", 0);
	sem_wait(philo->data->print_sem);
	print_action(get_time_elapsed(philo->data->start_time), philo->philo_num,
		THINK);
	sem_post(philo->data->print_sem);
	philo->next_state = EAT;
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
		{
			print_action(get_time_elapsed(philo->data->start_time),
				philo->philo_num, DEATH);
			exit(1);
		}
		if (philo->next_state == EAT && philo->data->num_of_philos > 1)
		{
			if (philo->eat_count >= philo->data->meals_count
				&& philo->data->meals_count != -1)
			{
				exit(0);
			}
			philo_eat(philo);
		}
		else if (philo->next_state == SLEEP)
			philo_sleep(philo);
		else if (philo->next_state == THINK)
			philo_think(philo);
	}
	return (NULL);
}

void	run_simulation(t_data *data)
{
	int		i;
	int		status;
	pid_t	dead_pid;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(&data->philos[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	dead_pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) == 1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->philos[i].pid != dead_pid)
				kill(data->philos[i].pid, SIGKILL);
			i++;
		}
	}
}
