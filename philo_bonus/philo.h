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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DEATH,
	TOOK_FORK
};

typedef struct s_philo
{
	int				eat_count;
	long long		last_meal_time;
	enum e_state	next_state;
	int				philo_num;
	pid_t			pid;
}	t_philo;

typedef struct s_data
{
	long long		start_time;
	int				num_of_philos;
	int				meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philos;
	sem_t			*forks_sem;
	sem_t			*print_sem;
}	t_data;

int			ft_atoi(char *s);
int			are_valid_args(int ac, char **av);
t_data		*init_struct(int ac, char **av);
void		print_action(int time, int philo_num, enum e_state action);
void		run_simulation(t_data *data);
long long	get_current_time(void);
long long	get_time_elapsed(long long time);
void		monitoring(t_data *data);
int			check_death(t_data *data, t_philo *philo);
void		ft_mssleep(long long sleep_time);
void		clean_all(t_data *data);

#endif