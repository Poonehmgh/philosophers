/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:20:36 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/19 19:27:28 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool died_philo(t_philo_data *data)
{
	bool res;

	pthread_mutex_lock(&data->rules->died_philo_mutex);
	res = data->rules->died_philo_flag;
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
	return (res);
}

void *the_boss(void *a)
{
	t_philo_data	*data;
	int				i;

	data = *(t_philo_data **)a;
	i = 1;
	while (!died_philo(data)) 
	{
		if (i == data->rules->number_of_philos)
			i = 1;
		if (gettime_ms(&data[i]) - data[i].last_meal >= data[i].rules->die_time + 50)
		{
			pthread_mutex_lock(&data->rules->died_philo_mutex);
			data->rules->died_philo_flag = true;
			printf("\033[0;35mphilosopher %d is dead. last meal %ld  current time %ld\x1B[0m\n", *data[i].philo_id, data[i].last_meal, gettime_ms(&data[i]));	
			pthread_mutex_unlock(&data->rules->died_philo_mutex);
			return (NULL);
		}
		if (!died_philo(data) && data[i].number_of_meals == data->rules->min_meals)
		{
			printf("philosopher %d has eaten enough!\n", i);
			pthread_detach(data[i].thread);
		}
		i++;
	}
	return (NULL);
}

void *daily_schedule(void *a)
{
	t_philo_data	*data;

	data = a;
	while (!died_philo(data))
	{
		eating(data);
		sleep_think(data);
	}
	free(data->philo_id);
	return (NULL);
}
