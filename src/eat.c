/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:34:38 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/04 20:01:52 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	*fork_initializaition(t_philo_data *data)
{
	int	i;
	
	i = 1;
	while (i <= data[i].rules->number_of_philos)
	{
		if (i % 2 == 0)
		{
			data[i].forks.if_left_fork = true; // you can use this fork.
			data[i].forks.if_right_fork = true;
		}
		else
		{
			data[i].forks.if_left_fork = false;
			data[i].forks.if_right_fork = false;
		}
		if (i == data[i].rules->number_of_philos)
			data[i].forks.if_left_fork = data[1].forks.if_right_fork;
		i++;
	}

    return (NULL);
}

void    *eating(t_philo_data *data)
{
    int which_philosopher = *data->philo_id;
	(void)which_philosopher;
    return (NULL);
}