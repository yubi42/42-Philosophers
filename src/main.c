/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:20:00 by yubi42            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:51 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error: Not the right amount of input\n", 37);
		return (1);
	}
	if (input_invalid(ac, av))
		return (1);
	if (!set_data(&data, ac, av))
	{
		write(2, "Error: Unable to allocate memory\n", 32);
		return (1);
	}
	if (!set_philos(&philo, data))
	{
		write(2, "Error: Unable to allocate memory\n", 32);
		return (1);
	}
	if (edge_cases(data, philo))
		return (0);
	create_threads(philo);
	clean_up(&data, &philo, data.count);
}
