/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:20:00 by yubi42            #+#    #+#             */
/*   Updated: 2024/01/05 15:19:05 by jborner          ###   ########.fr       */
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
	create_threads(philo);
	clean_up(&data, &philo, data.count);
}
