/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:07:17 by yubi42            #+#    #+#             */
/*   Updated: 2023/11/10 11:02:42 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_forks_r_l(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(philo->data.forks[philo->id - 1]));
	if (check_any_philo_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data.forks[philo->id - 1]));
		return (0);
	}
	data->has_fork[philo->id - 1] = philo->id;
	printf("%lld %ld has taken a fork\n", timestamp_ms(), philo->id);
	pthread_mutex_lock(&(philo->data.forks[philo->id % philo->data.count]));
	if (check_any_philo_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data.forks[philo->id - 1]));
		pthread_mutex_unlock(&(philo->data.forks[philo->id
				% philo->data.count]));
		return (0);
	}
	data->has_fork[philo->id % philo->data.count] = philo->id;
	printf("%lld %ld has taken a fork\n", timestamp_ms(), philo->id);
	return (1);
}

int	pick_up_forks_l_r(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(philo->data.forks[philo->id % philo->data.count]));
	if (check_any_philo_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data.forks[philo->id
				% philo->data.count]));
		return (0);
	}
	data->has_fork[philo->id % philo->data.count] = philo->id;
	printf("%lld %ld has taken a fork\n", timestamp_ms(), philo->id);
	pthread_mutex_lock(&(philo->data.forks[philo->id - 1]));
	if (check_any_philo_dead(philo))
	{
		pthread_mutex_unlock(&(philo->data.forks[philo->id - 1]));
		pthread_mutex_unlock(&(philo->data.forks[philo->id
				% philo->data.count]));
		return (0);
	}
	data->has_fork[philo->id - 1] = philo->id;
	printf("%lld %ld has taken a fork\n", timestamp_ms(), philo->id);
	return (1);
}

int	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2)
		if (!pick_up_forks_r_l(philo, &(philo->data)))
			return (0);
	if (!(philo->id % 2))
		if (!pick_up_forks_l_r(philo, &(philo->data)))
			return (0);
	return (1);
}
