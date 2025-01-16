/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:47 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/16 13:56:41 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mssleep(long long sleep_time)
{
	long long	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
		usleep(100);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].next_state = THINK;
		data->philos[i].philo_num = i + 1;
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
}

void	init_semaphores(t_data *data)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("waiter_sem");
	sem_unlink("death_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->num_of_philos);
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	data->waiter_sem = sem_open("waiter_sem", O_CREAT, 0644, data->num_of_philos
			/ 2);
	data->death_sem = sem_open("death_sem", O_CREAT, 0644, 1);
}

t_data	*init_struct(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_count = ft_atoi(av[5]);
	else
		data->meals_count = -1;
	data->start_time = get_current_time();
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (free(data), NULL);
	init_semaphores(data);
	init_philos(data);
	return (data);
}

void	clean_all(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	free(data->philos);
	free(data);
}
