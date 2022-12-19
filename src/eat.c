/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/19 20:48:32 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void red()
{
  printf("\033[1;31m");
}

void yellow()
{
  printf("\033[1;33m");
}

void green()
{
  printf("\033[0;32m");
}

void white()
{
  printf("\033[0m");
}



char *food(int i)
{
	char *s[9] = {
		"Ghorme Sabzi.",
		"Hamburger.",
		"Pizza.",
		"Adas Polo.",
		"Pasta with Pesto Sause.",
		"Bratwurst.",
		"Soup.",
		"Aaaash.",
	};
	return (s[i]);
}

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
			print_msg("is eating", data, yellow, food(gettime_ms(data) % 7));
			pthread_mutex_lock(&data->meal_mutex);
			data->last_meal = gettime_ms(data);
			usleep_modified(data->rules->eat_time, data);
			data->number_of_meals += 1;
			if(!died_philo(data))
				print_msg("finished eating.", data, green, "");
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
