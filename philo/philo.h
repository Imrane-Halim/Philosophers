/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:38:41 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/01 15:54:24 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			eat_times;
	int			n_forks;
	int			is_dead;
	int			philo_num;
	pthread_t	th_id;
}	t_philo;

typedef struct s_data
{
	struct timeval	timestamp_start;
	int				num_of_philos;
	int				times_to_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	mutex_fork;
	t_philo			*philos;
}	t_data;

int	ft_atoi(char *s);
int	are_valid_args(int ac, char **av);

#endif