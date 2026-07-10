/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:24:46 by makoon            #+#    #+#             */
/*   Updated: 2025/04/15 13:57:19 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_data *data)
{
	if (is_valid_input(argc, argv) == 1)
		return (1);
	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_limit_meals = ft_atoi(argv[5]);
	else
		data->nbr_limit_meals = -1;
	return (0);
}

int	all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	(void) argc;
	while (argv[i])
	{
		if (all_digit(argv[i]) == 1)
			return (1);
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb <= 0))
			return (1);
		if (i != 1 && (nb <= 0))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

int	count_philo_full(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&data->death_mutex);
	while (i < data->philo_nbr)
	{
		if (data->philos[i].philo_full)
			count++;
		i++;
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (count);
}
