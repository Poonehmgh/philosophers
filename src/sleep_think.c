/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/20 20:12:56 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	print_msg(char *s, t_philo_data *data, void (*f)(), char *food)
{
	f();
	pthread_mutex_lock(&data->rules->died_philo_mutex);
	printf("%ld	philosopher %d %s %s\n", gettime_ms(data), \
			*data->philo_id, s, food);
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
}

/**
 * @brief this function makes sure that if someone dies in the middle of any
 *  act, the program
 * stops. bcz it keeps sleeping steps small.
 * @param time is the time in ms that we want to usleep.
 * @param data info for the use of gettime function. 
 */

void	usleep_modified(int time, t_philo_data *data)
{
	int	start;

	start = gettime_ms(data);
	while (1 && !died_philo(data))
	{
		if (gettime_ms(data) - start >= time)
			break ;
	}	
}

bool	am_i_hungry(t_philo_data *data)
{
	int	left_time_b4_dieing;
	int	now;

	now = gettime_ms(data);
	pthread_mutex_lock(&data->meal_mutex);
	left_time_b4_dieing = data->rules->die_time + data->last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if (left_time_b4_dieing - 1.4 * data->rules->eat_time <= gettime_ms(data))
		return (true);
	return (false);
}

void	sleep_think(t_philo_data *data)
{
	int	t;

	t = 0;
	if (!died_philo(data))
		print_msg("is sleeping.", data, white, "");
	if (!died_philo(data))
		usleep_modified(data->rules->sleep_time, data);
	if (!died_philo(data))
		print_msg("is thinking.", data, white, "");
	t = 0;
	while (!am_i_hungry(data) && !died_philo(data))
	{
		usleep_modified(t, data);
		t += 100;
	}
}
