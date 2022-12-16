/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/16 20:08:51 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool counter(t_philo_data *data,int a, time_t b)
{
	bool res;
	pthread_mutex_lock(&data->rules->counter);
	if (a < b)
		res = true;
	else
		res = false;
	pthread_mutex_unlock(&data->rules->counter);
	return (res);
}

bool	red_flag(t_philo_data *data)
{
	int left_time_b4_dieing;
	int now;

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
	
	printf("%ld: Philospher %d has started sleeping\n", gettime_ms(data), *data->philo_id);
	while (!died_philo(data) && counter(data, t, data->rules->sleep_time))
	{
		usleep(t * 1000);
		t += 100;
	}
	// printf("%ld: Philospher %d has finished sleeping\n", gettime_ms(data), *data->philo_id);
	if (data->rules->died_philo_flag)
		return;
	printf("%ld: Philospher %d has started thinking\n", gettime_ms(data), *data->philo_id);
	t = 0;
	while (!data->rules->died_philo_flag && !red_flag(data))
	{
		usleep(t);
		t += 10;
	}
	// printf("%ld: Philospher %d has ended thinking\n", gettime_ms(data), *data->philo_id);
}
