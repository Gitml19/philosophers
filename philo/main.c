/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:08:24 by makoon            #+#    #+#             */
/*   Updated: 2025/04/14 17:04:06 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_data *data, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Invalid number of arguments\n"
			"Usage :./philo num_philos time_to_die time_to_eat "
			"time_to_sleep [num_meals]\n");
		return (1);
	}
	if (check_args(argc, argv, data) == 1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(data) || init_mutex(data) || init_philo(data))
	{
		clean_data(data);
		printf("Error: Initialization failed\n");
		return (1);
	}
	return (0);
}

int	start_simulation(t_data *data)
{
	if (create_thread_philo(data))
	{
		clean_data(data);
		printf("Error: Could not create threads\n");
		return (1);
	}
	if (wait_for_threads(data))
	{
		clean_data(data);
		printf("Error: Could not join threads\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_simulation(&data, argc, argv))
		return (1);
	if (start_simulation(&data))
		return (1);
	clean_data(&data);
	return (0);
}
