/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:20:00 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 19:59:09 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (error(ac, av, &data, &philo))
		return (1);
	if (edge_cases(data, philo))
		return (0);
	printf("%li\n", data.must_eat);
	create_threads(philo);
	clean_up(&data, &philo, data.count);
}
