/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:53 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/04 20:00:57 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<pthread.h>
# include<stdlib.h>
# include<sys/time.h>
# include<stdbool.h>

typedef struct timings
{
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int think_time;
	pthread_mutex_t mutex;
	time_t	start_time;
	int		number_of_philos;
	time_t	time_left_to_die;
}	t_rules;


typedef struct fork
{
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
	bool			if_right_fork;
	bool			if_left_fork;
} t_fork;

typedef struct philo_data
{
	pthread_t thread;
	int	*philo_id;
	int	task;
	time_t	last_meal;
	t_rules			*rules;
	t_fork			forks;
}	t_philo_data;

int		ft_atoi(const char *str);
void	*fork_initializaition(t_philo_data *data);
void    *eating(t_philo_data *data);



#endif