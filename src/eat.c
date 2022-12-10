/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/10 16:14:57 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool	take_right_fork(int id, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[id].fork);
	if (rules->forks[id].availability)
	{
		rules->forks[id].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&rules->forks[id].fork);
	return (false);
}

bool	take_left_fork(int id, t_rules *rules)
{
	if (id == rules->number_of_philos)
		id = 0;
	pthread_mutex_lock(&rules->forks[id + 1].fork);
	if (rules->forks[id + 1].availability)
	{
		rules->forks[id + 1].availability = false;
		return (true);
	}
	pthread_mutex_unlock(&rules->forks[id + 1].fork);
	return (false);
}

void	*eating(t_philo_data *data)
{
	int	id;

	id = *data->philo_id;
	if (take_right_fork(id, data->rules))
	{
		if (take_left_fork(id, data->rules))
		{
			printf("\x1B[33m%ld philosopher %d has taken right fork.\n \x1B[0m", gettime_ms(data), id);
			printf("\x1B[33m%ld philosopher %d has taken the left fork.\n \x1B[0m", gettime_ms(data), id);
			pthread_mutex_lock(&data->mutex);
			data->last_meal += gettime_ms(data);
			usleep(1000 * data->rules->eat_time);
			printf("\x1B[34m%ldphilosopher %d finished eating.\n\x1B[0m", gettime_ms(data), *data->philo_id);
			data->number_of_meals += 1;
			data->rules->forks[id].availability = true;
			pthread_mutex_unlock(&data->mutex);
			pthread_mutex_unlock(&data->rules->forks[id + 1].fork);
			if (id == data->rules->number_of_philos)
				data->rules->forks[0].availability = true;
			else
				data->rules->forks[id + 1].availability = true;
			pthread_mutex_unlock(&data->rules->forks[id].fork);
		}	
	}
	return (NULL);
}
