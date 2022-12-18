/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/18 01:11:00 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool	take_right_fork(t_philo_data *data)
{

	pthread_mutex_lock(&data->rules->forks[*data->philo_id].fork);
	if (data->rules->forks[*data->philo_id].availability)
	{
		data->rules->forks[*data->philo_id].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
	return (false);
}
pthread_mutex_t test;

bool	take_left_fork(t_philo_data *data)
{
	pthread_mutex_lock(&test);
	int id = *data->philo_id;
	if (*data->philo_id == data->rules->number_of_philos)
		 id = 0;
	pthread_mutex_unlock(&test);
	pthread_mutex_lock(&data->rules->forks[id + 1].fork);
	if (data->rules->forks[id + 1].availability)
	{
		data->rules->forks[id + 1].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&data->rules->forks[id + 1].fork);
	return (false);
}

bool	eating(t_philo_data *data)
{
	if (take_right_fork(data) && !died_philo(data))
	{
		if (take_left_fork(data) && !died_philo(data))
		{
			printf("\x1B[33m%ld philosopher %d has taken right fork.\n \x1B[0m", gettime_ms(data), *data->philo_id);
			printf("\x1B[33m%ld philosopher %d has taken the left fork.\n \x1B[0m", gettime_ms(data), *data->philo_id);
			pthread_mutex_lock(&data->meal_mutex);
			data->last_meal = gettime_ms(data);
			usleep_modified(data->rules->eat_time, data);
			// usleep(1000 * data->rules->eat_time);
			data->number_of_meals += 1;
			if(!died_philo(data))
				printf("\x1B[34m%ldphilosopher %d finished eating. this was the %d meal.\n\x1B[0m", gettime_ms(data), *data->philo_id, data->number_of_meals);
			data->rules->forks[*data->philo_id].availability = true;
			pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
			pthread_mutex_unlock(&data->meal_mutex);
			if (*data->philo_id == data->rules->number_of_philos)
			{
				data->rules->forks[1].availability = true;
				pthread_mutex_unlock(&data->rules->forks[1].fork);
			}
			else
			{
				data->rules->forks[*data->philo_id + 1].availability = true;
				pthread_mutex_unlock(&data->rules->forks[*data->philo_id + 1].fork);
			}
			return (true);
		}
		else
		{
			data->rules->forks[*data->philo_id].availability = true;
			pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
		}
	}
	return (false);
}
