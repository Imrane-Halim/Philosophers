/* ************************************************************************** */
/*			                                                                  */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:38:41 by ihalim            #+#    #+#             */
/*   Updated: 2025/01/01 15:54:24 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int			eat_count;
	long long	last_meal_time;
	int			philo_num;
	pid_t		pid;
}				t_philo;

typedef struct s_data
{
	long long	start_time;
	int			num_of_philos;
	int			meals_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	t_philo		*philos;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*death_sem;
}				t_data;

typedef struct s_monitor
{
	t_data		*data;
	t_philo		*philo;
}				t_monitor;

// Conversion and Validation Functions
int			ft_atoi(char *s);
int			are_valid_args(int ac, char **av);

// Initialization Functions
t_data		*init_struct(int ac, char **av);

// Simulation Control Functions
void		run_simulation(t_data *data);

// Time Management Functions
long long	get_current_time(void);
long long	get_time_elapsed(long long time);
void		ft_mssleep(long long sleep_time);

// Monitoring Functions
void		*monitoring(void *data);
int			check_death(t_data *data, t_philo *philo);

// Utility Functions
void		print_action(int time, int philo_num, char *action);
void		clean_all(t_data *data);

#endif