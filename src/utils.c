/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:09:55 by yubi42            #+#    #+#             */
/*   Updated: 2023/11/20 20:40:40 by yubi42           ###   ########.fr       */
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

long long	timestamp_ms(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((long long)(cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
}

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
