/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/12 01:03:49 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool	take_right_fork(t_philo_data *data)
{

		printf("1 I am philo %d and I am here\n", *data->philo_id);
	pthread_mutex_lock(&data->rules->forks[*data->philo_id].fork);
	if (data->rules->forks[*data->philo_id].availability)
	{
		printf("2 I am philo %d and I am here and this is my fork %d\n", *data->philo_id, *data->philo_id);
		data->rules->forks[*data->philo_id].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
	return (false);
}
pthread_mutex_t test;
bool	take_left_fork(t_philo_data *data)
{
	int i = 1;
	while(i <= data->rules->number_of_philos)
	{
		printf("crazy crazy crazy fork %d %d\n", i, data->rules->forks[i].availability);
		i++;
	}
	pthread_mutex_lock(&test);
	int id = *data->philo_id;
	printf("3 I am philo %d and I am here\n", *data->philo_id);
	if (*data->philo_id == data->rules->number_of_philos)
		 id = 0;
	pthread_mutex_unlock(&test);
	pthread_mutex_lock(&data->rules->forks[id + 1].fork);
	if (data->rules->forks[id + 1].availability)
	{
		printf("4 I am philo %d and I am here this is my fork: %d\n", id, id + 1);
		data->rules->forks[id + 1].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&data->rules->forks[id + 1].fork);
	return (false);
}

bool	eating(t_philo_data *data)
{
	// if (*data->philo_id % 2 != 0)
	// 	usleep(2000);
	if (take_right_fork(data))
	{
		if (take_left_fork(data))
		{
			printf("\x1B[33m%ld philosopher %d has taken right fork.\n \x1B[0m", gettime_ms(data), *data->philo_id);
			printf("\x1B[33m%ld philosopher %d has taken the left fork.\n \x1B[0m", gettime_ms(data), *data->philo_id);
			pthread_mutex_lock(&data->meal_mutex);
			data->last_meal += gettime_ms(data);
			usleep(1000 * data->rules->eat_time);
			data->number_of_meals += 1;
			printf("\x1B[34m%ldphilosopher %d finished eating. this was the %d meal.\n\x1B[0m", gettime_ms(data), *data->philo_id, data->number_of_meals);
			data->rules->forks[*data->philo_id].availability = true;
			pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
			pthread_mutex_unlock(&data->meal_mutex);
			if (*data->philo_id == data->rules->number_of_philos)
			{
				data->rules->forks[1].availability = true;
				printf("fork 1 being changed here to be available\n");
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
