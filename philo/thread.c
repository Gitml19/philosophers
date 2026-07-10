/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:48:37 by makoon            #+#    #+#             */
/*   Updated: 2025/04/14 16:40:10 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stop(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->end_simulation;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_simulation_stop(data))
	{
		i = 0;
		while (i < data->philo_nbr && !is_simulation_stop(data))
		{
			if (check_philo_status(&data->philos[i], data))
				return (NULL);
			i++;
		}
		if (count_philo_full(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (1);
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_philo_status(t_philo *philo, t_data *data)
{
	long	current_time;
	int		stop_status;

	current_time = get_time();
	pthread_mutex_lock(&data->death_mutex);
	if (current_time - philo->last_meal_time > data->time_to_die)
	{
		print_message(philo, "died");
		pthread_mutex_lock(&data->write_mutex);
		data->end_simulation = true;
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	stop_status = data->end_simulation;
	pthread_mutex_unlock(&data->death_mutex);
	if (stop_status == 1)
		return (1);
	return (0);
}

int	all_philos_full(t_data *data)
{
	if (data->nbr_limit_meals > 0 && count_philo_full(data) == data->philo_nbr)
	{
		pthread_mutex_lock(&data->write_mutex);
		data->end_simulation = true;
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	return (0);
}
