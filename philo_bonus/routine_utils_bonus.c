/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/18 10:26:21 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(int time, int philo_num, char *action)
{
	sem_t	*print;

	print = sem_open("print_sem", 0);
	sem_wait(print);
	printf("%d\t%d ", time, philo_num);
	printf(" %s\n", action);
	sem_post(print);
}

int	check_death(t_monitor *monitor)
{
	sem_t	*death;
	sem_t	*print;

	print = sem_open("print_sem", 0);
	death = sem_open("death_sem", 0);
	sem_wait(death);
	if (get_time_elapsed(monitor->philo->last_meal_time)
		> monitor->data->time_to_die)
	{
		sem_wait(print);
		death->__align = 99;
		printf("%lld\t%d %s\n", get_time_elapsed(monitor->data->start_time),
			monitor->philo->philo_num, "died");
		sem_post(death);
		return (1);
	}
	sem_post(death);
	return (0);
}

void	*monitoring(void *arg)
{
	t_monitor	*monitor;
	sem_t		*death;

	monitor = (t_monitor *)arg;
	death = sem_open("death_sem", 0);
	while (1)
	{
		if (check_death(monitor))
			return (NULL);
		sem_wait(death);
		if (monitor->philo->eat_count >= monitor->data->meals_count
			&& monitor->data->meals_count != -1)
		{
			death->__align = 0;
			sem_post(death);
			break ;
		}
		sem_post(death);
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
