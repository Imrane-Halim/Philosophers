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
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
}	t_philo;

typedef struct s_data
{
	int		num_of_philos;
	t_philo	*philos;
}	t_data;

int	ft_atoi(char *s);
int	are_valid_args(int ac, char **av);

#endif