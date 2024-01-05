/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:17:20 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 15:54:53 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_forks(t_data *data)
{
	int	i;

	data->has_fork = NULL;
	data->has_fork = malloc(sizeof(long) * data->count);
	if (!data->has_fork)
		return (0);
	data->forks = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count);
	if (!data->forks)
	{
		free(data->has_fork);
		return (0);
	}
	i = 0;
	while (i < data->count)
	{
		if (pthread_mutex_init(&(data->forks[i++]), NULL) != 0)
		{
			clean_forks(data, i);
			return (0);
		}
	}
	return (1);
}

int	set_data(t_data *data, int ac, char **av)
{
	data->count = ft_atol(av[1]);
	if (data->count == 0)
		return (2);
	data->death_timer = ft_atol(av[2]);
	data->eating_time = ft_atol(av[3]) * 1000;
	data->sleeping_time = ft_atol(av[4]) * 1000;
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atol(av[5]);
	data->threads = NULL;
	data->threads = malloc(sizeof(pthread_t) * data->count);
	if (!data->threads)
		return (1);
	if (!set_forks(data))
	{
		free(data->threads);
		return (1);
	}
	data->start_ts = timestamp_ms(NULL);
	return (0);
}

void	create_new_philo(t_data data, t_philo **new_philo, int i)
{
	*new_philo = malloc(sizeof(t_philo));
	if (!(*new_philo))
		return ;
	(*new_philo)->id = i;
	if ((*new_philo)->id % 2 == 0)
		(*new_philo)->start_delay = 0;
	else
		(*new_philo)->start_delay = 500;
	(*new_philo)->dead = 0;
	if (pthread_mutex_init(&((*new_philo)->dead_mutex), NULL) != 0)
		return ;
	(*new_philo)->last_eaten = timestamp_ms(NULL);
	if (pthread_mutex_init(&((*new_philo)->last_eaten_mutex), NULL) != 0)
		return ;
	(*new_philo)->must_eat = data.must_eat;
	if (pthread_mutex_init(&((*new_philo)->must_eat_mutex), NULL) != 0)
		return ;
	(*new_philo)->data = data;
	(*new_philo)->next = NULL;
}

int	set_philos(t_philo **first_philo, t_data data)
{
	t_philo	*new_philo;
	t_philo	*tmp;
	int		i;

	*first_philo = NULL;
	new_philo = NULL;
	tmp = NULL;
	i = 0;
	while (++i <= data.count)
	{
		create_new_philo(data, &new_philo, i);
		if (!new_philo)
		{
			clean_up(&data, first_philo, i - 1);
			return (0);
		}
		if (!(*first_philo))
			*first_philo = new_philo;
		else
			tmp->next = new_philo;
		tmp = new_philo;
	}
	tmp->next = *first_philo;
	return (1);
}
