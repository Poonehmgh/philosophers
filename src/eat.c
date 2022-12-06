/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/06 13:08:42 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

// void	*fork_initializaition(t_philo_data *data)
// {
// 	int	i;
	
// 	i = 1;
// 	while (i <= data[i].rules->number_of_philos)
// 	{
// 		if (i % 2 == 0)
// 		{
// 			data[i].forks.if_left_fork = true; // you can use this fork.
// 			data[i].forks.if_right_fork = true;
// 		}
// 		else
// 		{
// 			data[i].forks.if_left_fork = false;
// 			data[i].forks.if_right_fork = false;
// 		}
// 		if (i == data[i].rules->number_of_philos)
// 			data[i].forks.if_left_fork = data[1].forks.if_right_fork;
// 		i++;
// 	}

//     return (NULL);
// }

bool take_right_fork (int id, t_rules *rules)
{
	if (rules->forks[id].availability)
	{
		pthread_mutex_lock(&rules->forks[id].right_fork);
		rules->forks[id].availability = false;
			return (true);
	}
	return (false);
}
bool take_left_fork(int id, t_rules *rules)
{
	if (id == rules->number_of_philos)
		id = 0;
	if (rules->forks[id + 1].availability)
	{
		pthread_mutex_lock(&rules->forks[id + 1].right_fork);
		rules->forks[id + 1].availability = false;
		return (true);
	}
	return (false);
}
void    *eating(t_philo_data *data)
{
	// (void)data;
    int which_philosopher = *data->philo_id;
	if (take_right_fork(which_philosopher, data->rules))
	{
		if (take_left_fork(which_philosopher, data->rules))
		{
			printf("\x1B[33m%ld philosopher %d has taken right fork.\n \x1B[0m", gettime_ms(data), which_philosopher);
			printf("\x1B[33m%ld philosopher %d has taken the left fork.\n \x1B[0m", gettime_ms(data), which_philosopher);
			pthread_mutex_lock(&data[which_philosopher].mutex);
			data[which_philosopher].last_meal += gettime_ms(data);
			pthread_mutex_unlock(&data[which_philosopher].mutex);
			usleep(1000 * data->rules->eat_time);
			printf("\x1B[34m%ldphilosopher %d finished eating.\n\x1B[0m", gettime_ms(data), *data->philo_id);
			data->number_of_meals += 1;
			pthread_mutex_unlock(&data->rules->forks[which_philosopher].right_fork);
			pthread_mutex_unlock(&data->rules->forks[which_philosopher + 1].right_fork);
			printf("this this this this this this and i am happy minishell is finished %d %ld\n", which_philosopher, data[which_philosopher].last_meal);

			printf("this this this this this this and i am happy minishell is finished after the assignement %d %ld\n", which_philosopher, data[which_philosopher].last_meal);
			data->rules->forks[which_philosopher].availability = true;
			if (which_philosopher == data->rules->number_of_philos)
				data->rules->forks[0].availability = true;
			else
				data->rules->forks[which_philosopher + 1].availability = true;
		
		}	
	}
    return (NULL);
}
