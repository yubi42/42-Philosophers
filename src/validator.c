/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:06 by yubi42            #+#    #+#             */
/*   Updated: 2023/11/20 20:45:47 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_invalid(int ac, char **av)
{
	if (ft_strlen(av[1]) > 19 || ft_strlen(av[2]) > 19 || ft_strlen(av[3]) > 19
		|| ft_strlen(av[4]) > 19)
	{
		write(2, "Error: Invalid input\n", 22);
		return (1);
	}
	if (ft_atol(av[1]) == -1 || ft_atol(av[2]) == -1 || ft_atol(av[3]) == -1
		|| ft_atol(av[4]) == -1)
	{
		write(2, "Error: Invalid input\n", 22);
		return (1);
	}
	if (ac == 6)
	{
		if (ft_atol(av[5]) == -1)
		{
			write(2, "Error: Invalid input\n", 22);
			return (1);
		}
	}
	return (0);
}

int	edge_cases(t_data data, t_philo *philo)
{
	if (data.count == 0 || data.must_eat == 0)
	{
		clean_up(&data, &philo, data.count);
		return (1);
	}
	if (data.count == 1)
	{
		printf("%lld 1 has taken a fork\n", timestamp_ms());
		usleep(philo->data.sleeping_time);
		printf("%lld 1 died\n", timestamp_ms());
		clean_up(&data, &philo, data.count);
		return (1);
	}
	return (0);
}
