/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/18 11:20:58 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	return (get_time_elapsed(philo->last_meal_time) > philo->data->time_to_die);
}

void	monitoring(t_data *data)
{
	int	i;
	int	full_philos;

	full_philos = 0;
	i = 0;
	while (full_philos != data->num_of_philos)
	{
		pthread_mutex_lock(&data->mutex);
		if (check_death(&data->philos[i]))
		{
			data->stop = 1;
			print_action(get_time_elapsed(data->start_time),
				data->philos[i].philo_num, "died");
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		if (data->philos[i].eat_count >= data->meals_count
			&& data->meals_count != -1)
			full_philos++;
		pthread_mutex_unlock(&data->mutex);
		i = (i + 1) % data->num_of_philos;
		usleep(100);
	}
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
