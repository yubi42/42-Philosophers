/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:16:04 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 16:00:20 by jborner          ###   ########.fr       */
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

typedef struct s_data
{
	long			count;
	long			start_ts;
	long			death_timer;
	long			eating_time;
	long			sleeping_time;
	long			must_eat;
	pthread_t		*threads;
	long			*has_fork;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	long			id;
	long			start_delay;
	int				dead;
	pthread_mutex_t	dead_mutex;
	long long		last_eaten;
	pthread_mutex_t	last_eaten_mutex;
	long			must_eat;
	pthread_mutex_t	must_eat_mutex;
	struct s_data	data;
	struct s_philo	*next;
}					t_philo;

// clean_up.c

void				clean_forks(t_data *data, int i);
void				clean_up(t_data *data, t_philo **philo,
						int cur_philo_count);

// monitoring.c

int					check_dead(t_philo *philo);
int					check_end(t_philo *philo);
void				*monitoring_philo(void *args);
void				create_threads(t_philo *philo);

// philo_actions.c

void				just_eaten_ts(t_philo *philo);
int					check_any_philo_dead(t_philo *philo);
int					check_done_eating(t_philo *philo);
void				*philo_actions(void *args);

// philo_actions_forks.c

int					pick_up_forks_r_l(t_philo *philo, t_data *data);
int					pick_up_forks_l_r(t_philo *philo, t_data *data);
int					pick_up_forks(t_philo *philo);

// set_structs.c

int					set_data(t_data *data, int ac, char **av);
void				create_new_philo(t_data data, t_philo **new_philo, int i);
int					set_philos(t_philo **first_philo, t_data data);

// utils.c

long				ft_atol(char *str);
long long			timestamp_ms(t_philo *philo);
size_t				ft_strlen(const char *s);

// validator.c

int					input_invalid(int ac, char **av);
int					edge_cases(t_data data, t_philo *philo);
int					error(int ac, char **av, t_data *data, t_philo **philo);

#endif