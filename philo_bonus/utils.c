/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:47 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/12 11:37:39 by marvin           ###   ########.fr       */
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
		data->philos[i].data = data;
		data->philos[i].n_forks = 1;
		data->forks[i] = sem_open("fork_sem", O_CREAT, 0644, 1);
		i++;
	}
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
	data->forks = malloc(sizeof(sem_t) * data->num_of_philos);
	if (!data->forks)
		return (free(data->philos), free(data), NULL);
	init_philos(data);
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	return (data);
}

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		sem_close(data->forks[i++]);
	sem_close(data->print_sem);
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	free(data->forks);
	free(data->philos);
	free(data);
}
