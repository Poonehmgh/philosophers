/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:53 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/10 14:34:13 by pmoghadd         ###   ########.fr       */
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
	pthread_mutex_t mutex;
	time_t	start_time;
	int		number_of_philos;
	time_t	time_left_to_die;
	t_fork			*forks;
	pthread_mutex_t	died_philo_mutex;
	bool			died_philo_flag;
}	t_rules;


typedef struct philo_data
{
	pthread_t thread;
	int	*philo_id;
	int	task;
	time_t	last_meal;
	int		number_of_meals;
	t_rules			*rules;
	pthread_mutex_t	mutex;
}	t_philo_data;

int		ft_atoi(const char *str);
void	*fork_initialization(t_philo_data *data);
void    *eating(t_philo_data *data);
time_t	gettime_ms(t_philo_data *data);
void    sleep_think(t_philo_data *data);
void *daily_schedule(void *a);



#endif