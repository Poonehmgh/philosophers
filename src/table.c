/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:01:15 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/20 15:04:21 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool	died_philo(t_philo_data *data)
{
	bool	res;
	bool	res2;

	pthread_mutex_lock(&data->rules->died_philo_mutex);
	res = data->rules->died_philo_flag;
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
	pthread_mutex_lock(&data->rules->ate_min_meal);
	res2 = data->rules->all_ate_flag;
	pthread_mutex_unlock(&data->rules->ate_min_meal);
	return (res | res2);
}

bool	all_philos_ate_enough(t_philo_data *data)
{
	int		i;
	int		tmp;

	i = 1;
	if (data->rules->min_meals == -1)
		return (false);
	while (i <= data->rules->number_of_philos)
	{
		pthread_mutex_lock(&data[i].meal_mutex);
		tmp = data[i].number_of_meals;
		pthread_mutex_unlock(&data[i].meal_mutex);
		if (tmp < data->rules->min_meals)
			break ;
		i++;
	}
	if (i == data->rules->number_of_philos + 1)
		return (true);
	return (false);
}

void	change_death_flag_announce_death(t_philo_data *data, int id)
{
	pthread_mutex_lock(&data->rules->died_philo_mutex);
	data[0].rules->died_philo_flag = true;
	printf("\033[1;31m%ld	philosopher %d is dead.\n", gettime_ms(data) - 5, id);
	// print_msg("is dead.", &data[i], red, "");
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
}

void	change_ate_flag_announce_enough(t_philo_data *data)
{
	pthread_mutex_lock(&data->rules->ate_min_meal);
	data->rules->all_ate_flag = true;
	printf("%ld	everyone ate enough.\n", gettime_ms(data));
	pthread_mutex_unlock(&data->rules->ate_min_meal);
}

void	*table(void *a)
{
	t_philo_data	*data;
	int				i;

	data = *(t_philo_data **)a;
	i = 1;
	while (!died_philo(data))
	{
		if (i == data->rules->number_of_philos)
			i = 1;
		if (gettime_ms(&data[i]) - data[i].last_meal >= data[i].rules \
				->die_time + 5)
		{
			change_death_flag_announce_death(data, i);
			return (NULL);
		}
		if (all_philos_ate_enough(data))
		{
			change_ate_flag_announce_enough(data);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
