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

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DEATH,
	TOOK_FORK
};

typedef struct s_data	t_data;
typedef struct s_philo
{
	int				eat_count;
	int				n_forks;
	long long		last_meal_time;
	enum e_state	next_state;
	int				philo_num;
	t_data			*data;
	pthread_t		th_id;
}	t_philo;

typedef struct s_data
{
	long long		start_time;
	int				num_of_philos;
	int				meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				stop;
	pthread_mutex_t	mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

int			ft_atoi(char *s);
int			are_valid_args(int ac, char **av);
t_data		*init_struct(int ac, char **av);
void		print_action(int time, int philo_num, enum e_state action);
void		run_simulation(t_data *data);
long long	get_current_time(void);
long long	get_time_elapsed(long long time);
void		monitoring(t_data *data);
int			check_death(t_philo *philo);
void		ft_mssleep(long long sleep_time);
void		clean_all(t_data *data);

#endif