/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/10 15:08:47 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	sleep_think(t_philo_data *data)
{
	int t = 0;
	printf("%ld: Philospher %d has started sleeping\n", gettime_ms(data), *data->philo_id);
	while (!data->rules->died_philo_flag && t <= data->rules->sleep_time)
	{
		usleep(t * 1000);
		// printf("t: %d timestamp %ld \n", t, gettime_ms(data));
		t += 100;
	}
	printf("%ld: Philospher %d has ended sleeping\n", gettime_ms(data), *data->philo_id);
	if (data->rules->died_philo_flag)
		return;
	printf("%ld: Philospher %d has started thinking\n", gettime_ms(data), *data->philo_id);
	t = 0;
	while (!data->rules->died_philo_flag && t <= data->rules->think_time)
	{
		usleep(t);
		t += 10;
	}
	printf("%ld: Philospher %d has ended thinking\n", gettime_ms(data), *data->philo_id);
}
