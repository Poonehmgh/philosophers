/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:37:56 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/16 17:40:19 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	free_atexit(t_philo_data *data, t_rules *rules, int num_philos)
{
	int	i;

	i = 0;
	if (rules)
	{
		free(rules);
		rules = NULL;
	}
	(void)num_philos;
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	clean_the_table(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i <= data->rules->number_of_philos)
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i <= data[0].rules->number_of_philos)
	{
		pthread_mutex_destroy(&data[i].meal_mutex);
		pthread_mutex_destroy(&data[i].rules->time_stamp);
		i++;
	}
}