/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:36:58 by makoon            #+#    #+#             */
/*   Updated: 2025/04/15 13:43:02 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//pour avoir un temps en millisecond
long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("gettimeofday() error\n"), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(long time_ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < time_ms)
		usleep(500);
}

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

void	print_message(t_philo *philo, char *message)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->end_simulation)
	{
		current_time = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", current_time, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}
