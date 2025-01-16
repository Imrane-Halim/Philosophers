/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/16 14:07:25 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int time, int philo_num, char *action)
{
	printf("%d\t%d ", time, philo_num);
	printf(" %s\n", action);
}

int	check_death(t_data *data, t_philo *philo)
{
	return (get_time_elapsed(philo->last_meal_time) > data->time_to_die);
}

void	*monitoring(void *arg)
{
	t_monitor	*monitor;
	sem_t		*death;
	sem_t		*print;

	death = sem_open("death_sem", 0);
	print = sem_open("print_sem", 0);
	monitor = (t_monitor *)arg;
	while (1)
	{
		sem_wait(death);
		if (check_death(monitor->data, monitor->philo))
		{
			sem_wait(print);
			print_action(get_time_elapsed(monitor->data->start_time),
				monitor->philo->philo_num, "died");
			exit(1);
		}
		sem_post(death);
		usleep(100);
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
