/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:01:15 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/25 15:02:49 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

/**
 * @brief this function returns true if the program should stop
 * (someone died or everyone ate enough meals) and false when everything is
 * fine for conutinueing. 
 * 
 * @param data 
 * @return true 
 * @return false 
 */
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

/**
 * @brief checks if everybody has ate at least the minimum amount
 * of meals.
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool	all_philos_ate_enough(t_philo_data *data)
{
	int		i;

	i = 1;
	if (data->rules->min_meals == -1)
		return (false);
	while (i <= data->rules->number_of_philos)
	{
		if (data[i].number_of_meals < data->rules->min_meals)
			break ;
		i++;
	}
	if (i == data->rules->number_of_philos + 1)
		return (true);
	return (false);
}

void	change_death_flag_announce_death(t_philo_data *data)
{
	pthread_mutex_lock(&data->rules->died_philo_mutex);
	data->rules->died_philo_flag = true;
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
	print_msg("is", data, red, "dead.");
}
/**
 * @brief this is to check if everyone ate enough.
 * 
 * @param data 
 */

void	change_ate_flag_announce_enough(t_philo_data *data)
{
	pthread_mutex_lock(&data->rules->ate_min_meal);
	data->rules->all_ate_flag = true;
	pthread_mutex_unlock(&data->rules->ate_min_meal);
	pthread_mutex_lock(&data->rules->printing);
	printf("%ld	everyone ate enough.\n", gettime_ms(data));
	pthread_mutex_unlock(&data->rules->printing);
}

/**
 * @brief this is the table, so each philosopher has access to this 
 * and can see if someone dies or if everyone ate enough. the reason why I
 *  named it table function, is to 
 * imply the 
 * fact that there is no correspondence between philosophers and a third party, 
 * which 
 * is not allowed in the problem.
 * this is simply all the information every philosopher has.
 * this is the only place where all the information of all the 
 * philosophers is available.
 * @param a this is an array of t_philo_data. each index is one philosopher.
 *  starting from 1. 
 * @return void* 
 */
void	*table(void *a)
{
	t_philo_data	*data;
	int				i;

	data = *(t_philo_data **)a;
	i = 1;
	while (!died_philo(data))
	{
		if (i >= data->rules->number_of_philos)
			i = 1;
		if (gettime_ms(&data[i]) - data[i].last_meal >= data[i].rules \
				->die_time + 5)
		{
			change_death_flag_announce_death(&data[i]);
			return (NULL);
		}
		if (all_philos_ate_enough(data))
		{
			change_ate_flag_announce_enough(&data[i]);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
