/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:09:55 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 16:00:00 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	num;

	num = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			num = (num * 10) + (*str - '0');
			str++;
		}
		else
			return (-1);
	}
	return (num);
}

long long	timestamp_ms(t_philo *philo)
{
	struct timeval	cur_time;
	long long		ts;

	gettimeofday(&cur_time, NULL);
	if (philo == NULL)
		ts = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	else
		ts = ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000))
			- philo->data.start_ts;
	return (ts);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
