/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/24 15:46:51 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	eating(t_philo_data *data)
{
	int	tmp;

	if (*data->philo_id == data->rules->number_of_philos)
		tmp = 0;
	else
		tmp = *data->philo_id;
	pthread_mutex_lock(&data->rules->forks[*data->philo_id].fork);
	pthread_mutex_lock(&data->rules->forks[tmp + 1].fork);
	data->last_meal = gettime_ms(data);
	usleep(data->rules->eat_time * 1000);
	data->number_of_meals += 1;
	if (!died_philo(data))
		print_msg("is eating", data, green, dinner((*data->philo_id + gettime_ms(data)) % 9));
	pthread_mutex_unlock(&data->rules->forks[*data->philo_id].fork);
	pthread_mutex_unlock(&data->rules->forks[tmp + 1].fork);
}