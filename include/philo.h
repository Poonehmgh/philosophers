/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:53 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/16 19:40:01 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<pthread.h>
# include<stdlib.h>
# include<sys/time.h>
# include<stdbool.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

typedef struct fork
{
	pthread_mutex_t fork;
	bool			availability;
} t_fork;

typedef struct timings
{
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int think_time;
	int min_meals;
	time_t	start_time;
	int		number_of_philos;
	time_t	time_left_to_die;
	t_fork			*forks;
	bool			died_philo_flag;
	pthread_mutex_t	died_philo_mutex;
	pthread_mutex_t counter;
	pthread_mutex_t time_stamp;
}	t_rules;


typedef struct philo_data
{
	pthread_t thread;
	int	*philo_id;
	int	task;
	time_t	last_meal;
	int		number_of_meals;
	t_rules			*rules;
	pthread_mutex_t	meal_mutex;
}	t_philo_data;

int		ft_atoi(const char *str);
void	*fork_initialization(t_philo_data *data);
bool    eating(t_philo_data *data);
time_t	gettime_ms(t_philo_data *data);
void    sleep_think(t_philo_data *data);
void *daily_schedule(void *a);
bool died_philo(t_philo_data *data);
void	free_atexit(t_philo_data *data, t_rules *rules, int num_philos);
void clean_the_table(t_philo_data *data);
void data_init(t_philo_data *data, t_rules *rules);
void	rules_init(char **argv, t_rules *rules);
time_t	gettime_ms(t_philo_data *data);
bool	red_flag(t_philo_data *data);




#endif