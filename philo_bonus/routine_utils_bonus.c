/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/17 10:11:32 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(int time, int philo_num, char *action)
{
	printf("%d\t%d ", time, philo_num);
	printf(" %s\n", action);
}

int	check_death(t_data *data, t_philo *philo)
{
	sem_t *death;
	sem_t *print;
	death = sem_open("death_sem", 0);
	print = sem_open("print_sem", 0);
	sem_wait(death);
	if (get_time_elapsed(philo->last_meal_time) > data->time_to_die)
	{
		sem_wait(print);
		print_action(get_time_elapsed(data->start_time),
		philo->philo_num, "died");
		sem_post(death);
		return (1);
	}
	sem_post(death);
	return (0);
}

void	*monitoring(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_death(monitor->data, monitor->philo))
			exit(EXIT_FAILURE);
		if (monitor->data->num_of_philos <= 1)
			continue ;
		if (monitor->philo->eat_count >= monitor->data->meals_count && monitor->data->meals_count != -1)
			exit(EXIT_SUCCESS);
	}
	return (NULL);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_time_elapsed(long long time)
{
	return (get_current_time() - time);
}
