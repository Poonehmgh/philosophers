/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/17 00:55:32 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool	counter(t_philo_data *data, int a, time_t b)
{
	bool	res;

	pthread_mutex_lock(&data->rules->counter);
	if (a < b)
		res = true;
	else
		res = false;
	pthread_mutex_unlock(&data->rules->counter);
	return (res);
}

void	print_msg(char *s, t_philo_data *data)
{
	pthread_mutex_lock(&data->rules->died_philo_mutex);
	printf("%ld	philosopher %d %s\n", gettime_ms(data), *data->philo_id, s);
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
}


/**
 * @brief this function makes sure that if someone dies in the middle of any act, the program
 * stops. bcz it keeps sleeping steps small.
 * @param time is the time in ms that we want to usleep.
 * @param data info for the use of gettime function. 
 */

void	usleep_modified(int time, t_philo_data *data)
{
	int	end;

	end = gettime_ms(data) + time;
	while (gettime_ms(data) <= end)
		usleep(time);
}/// but it maked things much slower !! odd 


bool	red_flag(t_philo_data *data)
{
	int	left_time_b4_dieing;
	int	now;

	left_time_b4_dieing = data->rules->die_time + data->last_meal;
	now = gettime_ms(data);
	if (left_time_b4_dieing - 2 * data->rules->eat_time <= now)
	{
		return (true);}
	return (false);
}

void	sleep_think(t_philo_data *data)
{
	int t = 0;
	if (!died_philo(data))
		print_msg("started sleeping.", data);
	while (!died_philo(data) && t <= data->rules->sleep_time)
	{
		usleep(t * 1000);
		t += 100;
	}
	print_msg("ended sleeping.", data);
	if (!died_philo(data))
		print_msg("started thinking.", data);
	t = 0;
	while (!data->rules->died_philo_flag && !red_flag(data) && !died_philo(data))
	{
		usleep(t);
		t += 10;
	}
	print_msg("finished thinking.", data);
}
