/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:35:51 by marvin            #+#    #+#             */
/*   Updated: 2025/01/14 16:28:36 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int time, int philo_num, enum e_state action)
{
	printf("%d\t%d ", time, philo_num);
	if (action == TOOK_FORK)
		printf("has taken a fork\n");
	else if (action == DEATH)
		printf("died\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
}

int	check_death(t_data *data, t_philo *philo)
{
	return (get_time_elapsed(philo->last_meal_time) > data->time_to_die);
}

// void	monitoring(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (!data->stop)
// 	{
// 		if (check_death(&data->philos[i]))
// 		{
// 			data->stop = 1;
// 			data->philos[i].next_state = DEATH;
// 			print_action(get_time_elapsed(data->start_time),
// 				data->philos[i].philo_num, DEATH);
// 			break ;
// 		}
// 		i = (i + 1) % data->num_of_philos;
// 		usleep(100);
// 	}
// }

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
