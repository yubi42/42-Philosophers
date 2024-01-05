/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:06 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 16:00:03 by jborner          ###   ########.fr       */
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
		printf("%lld 1 has taken a fork\n", timestamp_ms(philo));
		usleep(philo->data.death_timer * 1000);
		printf("%lld 1 died\n", timestamp_ms(philo));
		clean_up(&data, &philo, data.count);
		return (1);
	}
	return (0);
}

int	error(int ac, char **av, t_data *data, t_philo **philo)
{
	int	errno;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error: Not the right amount of input\n", 37);
		return (1);
	}
	if (input_invalid(ac, av))
		return (1);
	errno = set_data(data, ac, av);
	if (errno)
	{
		if (errno == 1)
			write(2, "Error: Unable to allocate memory\n", 32);
		else
			write(2, "Error: Input at least 1 philosopher\n", 36);
		return (1);
	}
	if (!set_philos(philo, *data))
	{
		write(2, "Error: Unable to allocate memory\n", 32);
		return (1);
	}
	return (0);
}
