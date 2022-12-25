/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:09:40 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/25 15:06:42 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

/**
 * @brief to make sure that there would be no printing after
 * someone dies or when everyone eats enough, 
 * for printing we use mutexes.
 * 
 * @param s 
 * @param data 
 * @param f 
 * @param food 
 */
void	print_msg(char *s, t_philo_data *data, void (*f)(), char *food)
{
	f();
	pthread_mutex_lock(&data->rules->printing);
	if (!data->rules->died_philo_flag && !data->rules->all_ate_flag)
		printf("%ld	philosopher %d %s %s\n", gettime_ms(data), \
			*data->philo_id, s, food);
	pthread_mutex_unlock(&data->rules->printing);
}

/**
 * @brief this function makes sure that if someone dies in the middle of any
 *  act, the program
 * stops. bcz it keeps sleeping steps small.
 * @param time is the time in ms that we want to usleep.
 * @param data info for the use of gettime function. 
 */

void	usleep_modified(int time, t_philo_data *data)
{
	int	start;

	start = gettime_ms(data);
	while (!died_philo(data))
	{
		if (gettime_ms(data) - start >= time)
			break ;
	}	
}

/**
 * @brief this function proceeds the sleeping and if someone dies 
 * in the middle of sleeping time, then the program wont print anything.  
 * 
 * @param data 
 */
void	sleep_think(t_philo_data *data)
{
	if (!data->rules->died_philo_flag && !data->rules->all_ate_flag)
		print_msg("is sleeping.", data, yellow, "");
	if (!died_philo(data))
		usleep(data->rules->sleep_time * 1000);
	if (!data->rules->died_philo_flag && !data->rules->all_ate_flag)
		print_msg("is thinking.", data, white, "");
}
