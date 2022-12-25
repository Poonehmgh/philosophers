/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/25 12:58:39 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

/**
 * @brief eat function locks each fork and then changes the variable 
 * last meal and variable number of meals.
 * if the number of philosophers is 1, then the eating
 * act cannot be done since there is only one fork. 
 * so, it returns false in that case. 
 * @param data the data contains information of each philosopher.
 */
bool	eating(t_philo_data *data)
{
	int	tmp;

	if (*data->philo_id == data->rules->number_of_philos)
		tmp = 0;
	else
		tmp = *data->philo_id;
	if (data->rules->number_of_philos == 1)
		return (false);
	pthread_mutex_lock(&data->rules->forks[*data->philo_id].fork);
	pthread_mutex_lock(&data->rules->forks[tmp + 1].fork);
	data->last_meal = gettime_ms(data);
	if (!died_philo(data))
		print_msg("is eating", data, green, \
			dinner((*data->philo_id + gettime_ms(data)) % 9));
	usleep(data->rules->eat_time * 1000);
	data->number_of_meals += 1;
	pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
	pthread_mutex_unlock(&data->rules->forks[tmp + 1].fork);
	return (true);
}
