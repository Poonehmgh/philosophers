/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:37:56 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/20 19:53:39 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	free_atexit(t_philo_data *data, t_rules *rules)
{
	int	i;

	i = 1;
	if (rules->forks)
	{
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules)
	{
		free(rules);
		rules = NULL;
	}
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
		i++;
	}
	free_atexit(data, data->rules);
}
