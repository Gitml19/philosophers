/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makoon <makoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:11:44 by makoon            #+#    #+#             */
/*   Updated: 2025/04/14 18:07:47 by makoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_limit_meals;
	bool				end_simulation;
	long				start_time;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				last_meal_time;
	int					meals_eaten;
	bool				philo_full;
	t_data				*data;
}						t_philo;

int					init_data(t_data *data);
int					init_mutex(t_data *data);
int					init_philo(t_data *data);
int					create_thread_philo(t_data *data);

int					check_args(int argc, char **argv, t_data *data);
int					all_digit(char *str);
int					is_valid_input(int argc, char **argv);
int					ft_atoi(const char *nptr);

long				get_time(void);
void				precise_sleep(long time_ms);
void				clean_data(t_data *data);
void				print_message(t_philo *philo, char *message);

int					is_simulation_stop(t_data *data);
void				*death_monitor(void *arg);
int					wait_for_threads(t_data *data);
int					all_philos_full(t_data *data);
int					check_philo_status(t_philo *philo, t_data *data);
int					count_philo_full(t_data *data);

void				take_fork(t_philo *philo);
void				eat(t_philo *philo);
void				release_forks(t_philo *philo);
void				sleep_routine(t_philo *philo);
void				think(t_philo *philo);
void				*philo_routine(void *arg);

#endif