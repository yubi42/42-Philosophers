/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:43 by yubi42            #+#    #+#             */
/*   Updated: 2023/11/09 14:24:40 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_forks(t_data *data, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->forks);
}

void	clean_up(t_data *data, t_philo **philo, int cur_philo_count)
{
	t_philo		*tmp;

	if (data->threads)
		free(data->threads);
	if (data->forks)
		clean_forks(data, data->count);
	if (data->has_fork)
		free(data->has_fork);
	while (cur_philo_count > 0)
	{
		tmp = (*philo)->next;
		pthread_mutex_destroy(&((*philo)->must_eat_mutex));
		pthread_mutex_destroy(&((*philo)->dead_mutex));
		free(*philo);
		*philo = tmp;
		cur_philo_count--;
	}
}
