/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:53 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/25 15:07:00 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<pthread.h>
# include<stdlib.h>
# include<sys/time.h>
# include<stdbool.h>
# include<sys/wait.h>
# include<sys/types.h>
# include<unistd.h>

typedef struct fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef struct timings
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				min_meals;
	time_t			start_time;
	int				number_of_philos;
	t_fork			*forks;
	bool			died_philo_flag;
	bool			all_ate_flag;
	pthread_mutex_t	died_philo_mutex;
	pthread_mutex_t	ate_min_meal;
	pthread_mutex_t	printing;
}	t_rules;

typedef struct philo_data
{
	pthread_t		thread;
	int				*philo_id;
	time_t			last_meal;
	int				number_of_meals;
	t_rules			*rules;
	pthread_mutex_t	meal_mutex;
}	t_philo_data;

int		ft_atoi(const char *str);
void	*fork_initialization(t_philo_data *data);
bool	eating(t_philo_data *data);
time_t	gettime_ms(t_philo_data *data);
void	sleep_think(t_philo_data *data);
void	*daily_schedule(void *a);
bool	died_philo(t_philo_data *data);
void	free_atexit(t_philo_data *data, t_rules *rules);
void	clean_the_table(t_philo_data *data);
void	data_init(t_philo_data *data, t_rules *rules);
void	rules_init(char **argv, t_rules *rules);
time_t	gettime_ms(t_philo_data *data);
bool	red_flag(t_philo_data *data);
void	usleep_modified(int time, t_philo_data *data);
void	print_msg(char *s, t_philo_data *data, \
		void (*f)(), char *food);
void	red(void);
void	yellow(void);
void	green(void);
void	white(void);
char	*dinner(int i);
void	*table(void *a);
void	err(char *s);
void	arg_check(char **argv);

#endif