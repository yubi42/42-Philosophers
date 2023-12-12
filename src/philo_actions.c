/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:03:22 by yubi42            #+#    #+#             */
/*   Updated: 2023/12/12 14:33:04 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	just_eaten_ts(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eaten_mutex));
	philo->last_eaten = timestamp_ms();
	pthread_mutex_unlock(&(philo->last_eaten_mutex));
}

int	check_any_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dead_mutex));
	if (philo->dead)
	{
		pthread_mutex_unlock(&(philo->dead_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->dead_mutex));
	return (0);
}

int	check_done_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->must_eat_mutex));
	philo->must_eat--;
	if (philo->must_eat == 0)
	{
		pthread_mutex_unlock(&(philo->must_eat_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->must_eat_mutex));
	return (0);
}

void	*philo_actions(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	just_eaten_ts(philo);
	printf("%lld %ld is thinking\n", timestamp_ms(), philo->id);
	usleep(philo->start_delay);
	while (1)
	{
		if (!pick_up_forks(philo))
			return (NULL);
		printf("%lld %ld is eating\n", timestamp_ms(), philo->id);
		just_eaten_ts(philo);
		usleep(philo->data.eating_time);
		pthread_mutex_unlock(&(philo->data.forks[philo->id - 1]));
		pthread_mutex_unlock(&(philo->data.forks[philo->id
				% philo->data.count]));
		if (check_any_philo_dead(philo) || check_done_eating(philo))
			return (NULL);
		printf("%lld %ld is sleeping\n", timestamp_ms(), philo->id);
		usleep(philo->data.sleeping_time);
		if (check_any_philo_dead(philo))
			return (NULL);
		printf("%lld %ld is thinking\n", timestamp_ms(), philo->id);
		usleep(1000);
	}
}
