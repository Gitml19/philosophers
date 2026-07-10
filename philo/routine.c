/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:01:20 by makoon            #+#    #+#             */
/*   Updated: 2025/04/14 18:07:55 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		while (!is_simulation_stop(philo->data))
			usleep(1000);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->nbr_limit_meals)
		philo->philo_full = true;
	pthread_mutex_unlock(&philo->data->death_mutex);
	precise_sleep(philo->data->time_to_eat);
}

void	release_forks(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
		pthread_mutex_unlock(philo->left_fork);
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	sleep_routine(t_philo *philo)
{
	print_message(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->nbr_limit_meals)
		i = philo->data->nbr_limit_meals;
	else
		i = 1;
	while (i-- && !is_simulation_stop(philo->data))
	{
		take_fork(philo);
		eat(philo);
		release_forks(philo);
		sleep_routine(philo);
		think(philo);
		if (philo->data->nbr_limit_meals == -1)
			i += 1;
	}
	return (NULL);
}
