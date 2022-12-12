/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/12 00:37:58 by pooneh           ###   ########.fr       */
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

void	sleep_think(t_philo_data *data)
{
	int t = 0;
	// printf("%ld: Philospher %d has started sleeping\n", gettime_ms(data), *data->philo_id);
	while (!died_philo(data) && counter(data, t, data->rules->sleep_time))
	{
		usleep(t * 1000);
		// printf("t: %d timestamp %ld \n", t, gettime_ms(data));
		pthread_mutex_lock(&data->rules->counter);
		t += 100;
		pthread_mutex_unlock(&data->rules->counter);
	}
	// printf("%ld: Philospher %d has ended sleeping\n", gettime_ms(data), *data->philo_id);
	if (data->rules->died_philo_flag)
		return;
	// printf("%ld: Philospher %d has started thinking\n", gettime_ms(data), *data->philo_id);
	t = 0;
	while (!data->rules->died_philo_flag && t <= data->rules->think_time)
	{
		usleep(t);
		t += 10;
	}
	// printf("%ld: Philospher %d has ended thinking\n", gettime_ms(data), *data->philo_id);
}
