/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:58:13 by yubi42            #+#    #+#             */
/*   Updated: 2023/11/10 11:01:36 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eaten_mutex));
	if ((timestamp_ms() - philo->last_eaten) >= philo->data.death_timer)
	{
		pthread_mutex_unlock(&(philo->last_eaten_mutex));
		pthread_mutex_lock(&(philo->dead_mutex));
		philo->dead = 1;
		pthread_mutex_unlock(&(philo->dead_mutex));
		printf("%lld %ld died\n", timestamp_ms(), philo->id);
		return (1);
	}
	pthread_mutex_unlock(&(philo->last_eaten_mutex));
	return (0);
}

int	check_end(t_philo *philo)
{
	int	counter;
	int	i;

	i = 0;
	counter = philo->data.count;
	while (i < philo->data.count)
	{
		pthread_mutex_lock(&(philo->must_eat_mutex));
		if (philo->must_eat == 0)
			counter--;
		pthread_mutex_unlock(&(philo->must_eat_mutex));
		if (check_dead(philo))
			return (0);
		philo = philo->next;
		i++;
	}
	return (counter);
}

void	*monitoring_philo(void *args)
{
	int		i;
	t_philo	*philo;
	t_philo	*copy;

	philo = (t_philo *)args;
	copy = philo;
	while (1)
		if (check_end(copy) == 0)
			break ;
	i = 0;
	while (i < copy->data.count)
	{
		pthread_mutex_lock(&(copy->dead_mutex));
		copy->dead = 1;
		pthread_mutex_unlock(&(copy->dead_mutex));
		copy = copy->next;
		i++;
	}
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < philo->data.count)
	{
		if (pthread_create(&(philo->data.threads)[i], NULL, philo_actions,
			philo) != 0)
		{
			printf("Error: Not able to create threads\n");
			return ;
		}
		philo = philo->next;
		i++;
	}
	pthread_create(&monitor, NULL, monitoring_philo, philo);
	while (--i >= 0)
		pthread_join(philo->data.threads[i], NULL);
	pthread_join(monitor, NULL);
	return ;
}
