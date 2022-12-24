/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:57:08 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/23 16:30:13 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	gettime_ms(t_philo_data *data)
{
	struct timeval	tmp;
	time_t			res;

	gettimeofday(&tmp, NULL);
	res = tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (res - data->rules->start_time);
}

void	rules_init(char **argv, t_rules *rules)
{
	struct timeval	t;
	int				i;

	gettimeofday(&t, NULL);
	rules->start_time = t.tv_sec * 1000 + t.tv_usec * 0.001;
	rules->die_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->number_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		rules->min_meals = ft_atoi(argv[5]);
	else
		rules->min_meals = -1;
	rules->forks = malloc(sizeof(t_fork) * (rules->number_of_philos + 1));
	rules->died_philo_flag = false;
	rules->all_ate_flag = false;
	i = 1;
	while (i <= rules->number_of_philos + 1)
	{
		rules->forks[i].availability = true;
		i++;
	}
}

void	data_init(t_philo_data *data, t_rules *rules)
{
	int	i;

	i = 0;
	while (i <= rules->number_of_philos)
	{
		data[i].rules = rules;
		i++;
	}
	i = 0;
	while (i <= rules->number_of_philos)
	{
		data[i].last_meal = 0;
		data[i].number_of_meals = 0;
		i++;
	}
}
