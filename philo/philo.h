/* ************************************************************************** */
/*		                                                                     */
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

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo
{
	int					eat_count;
	long long			last_meal_time;
	int					philo_num;
	t_data				*data;
	pthread_t			th_id;
}						t_philo;

typedef struct s_data
{
	long long			start_time;
	int					num_of_philos;
	int					meals_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					stop;
	pthread_mutex_t		mutex;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_data;

// Utility Functions
int			ft_atoi(char *s);
long long	get_current_time(void);
long long	get_time_elapsed(long long time);
void		ft_mssleep(long long sleep_time);

// Argument Validation and Initialization
int			are_valid_args(int ac, char **av);
t_data		*init_struct(int ac, char **av);

// Simulation Control
void		run_simulation(t_data *data);
void		monitoring(t_data *data);
int			check_death(t_philo *philo);

// Philosopher Actions
void		print_action(int time, int philo_num, char *action);
void		clean_all(t_data *data);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		*routine(void *arg);

#endif