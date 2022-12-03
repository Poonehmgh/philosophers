/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:53 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/03 15:40:51 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<pthread.h>
# include<stdlib.h>
# include<sys/time.h>

typedef struct timings
{
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int think_time;
	pthread_mutex_t mutex;
	struct timeval	run_time;
}	t_rules;

typedef struct philo_data
{
	pthread_t thread;
	int	*philo_id;
	int	task;
	int	last_meal;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
	t_rules			*rules;
}	t_philo_data;


int		ft_atoi(const char *str);


#endif