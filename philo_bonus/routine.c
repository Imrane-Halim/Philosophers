/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/16 13:44:32 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_eat(t_data *data, t_philo *philo)
{
    sem_t   *print;
    sem_t   *forks;
    sem_t   *waiter;
    sem_t   *death;

    print = sem_open("print_sem", 0);
    forks = sem_open("forks_sem", 0);
    waiter = sem_open("waiter_sem", 0);
    death = sem_open("death_sem", 0);
    
    sem_wait(waiter);  // Only half of philosophers can try to eat at once
    
    sem_wait(death);   // Protect last_meal_time access
    sem_wait(print);
    if (get_time_elapsed(philo->last_meal_time) > data->time_to_die)
    {
        sem_post(print);
        sem_post(death);
        sem_post(waiter);
        return;
    }
    sem_post(print);
    sem_post(death);
    
    sem_wait(forks);
    
    sem_wait(forks);
    sem_wait(death);
    sem_wait(print);
    print_action(get_time_elapsed(data->start_time), philo->philo_num, TOOK_FORK);
    print_action(get_time_elapsed(data->start_time), philo->philo_num, EAT);
    philo->last_meal_time = get_current_time();
    philo->eat_count++;
    sem_post(print);
    sem_post(death);
    
    ft_mssleep(data->time_to_eat);
    sem_post(forks);
    sem_post(forks);
    sem_post(waiter);
    philo->next_state = SLEEP;
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	sem_t	*print;

	print = sem_open("print_sem", 0);
	sem_wait(print);
	print_action(get_time_elapsed(data->start_time), philo->philo_num, SLEEP);
	sem_post(print);
	ft_mssleep(data->time_to_sleep);
	philo->next_state = THINK;
}

void	philo_think(t_data *data, t_philo *philo)
{
	sem_t	*print;

	print = sem_open("print_sem", 0);
	sem_wait(print);
	print_action(get_time_elapsed(data->start_time), philo->philo_num, THINK);
	sem_post(print);
	philo->next_state = EAT;
}

void	routine(t_data *data, t_philo *philo)
{
	pthread_t	th_monitor;
	t_monitor	monitor;

	monitor.data = data;
	monitor.philo = philo;
	pthread_create(&th_monitor, NULL, monitoring, (void *)(&monitor));
	while (1)
	{
		if (philo->next_state == EAT && data->num_of_philos > 1)
		{
			if (philo->eat_count >= data->meals_count && data->meals_count
				!= -1)
				break ;
			philo_eat(data, philo);
		}
		else if (philo->next_state == SLEEP)
			philo_sleep(data, philo);
		else if (philo->next_state == THINK)
			philo_think(data, philo);
	}
	exit(1);
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
			routine(data, &data->philos[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	dead_pid = waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) != 1)
		return ;
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].pid != dead_pid)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}
