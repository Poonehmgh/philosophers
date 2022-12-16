/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/16 20:32:12 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool died_philo(t_philo_data *data)
{
	bool res;

	pthread_mutex_lock(&data->rules->died_philo_mutex);
	res = data->rules->died_philo_flag;
	pthread_mutex_unlock(&data->rules->died_philo_mutex);
	return (res);
}

void *the_boss(void *a)
{
	t_philo_data	*data;
	int				i;

	data = *(t_philo_data **)a;
	i = 1;
	while (!died_philo(data))
	{
		if (i == data->rules->number_of_philos)
			i = 1;
		if (gettime_ms(&data[i]) - data[i].last_meal >= data[i].rules->die_time)
		{
			pthread_mutex_lock(&data->rules->died_philo_mutex);
			data->rules->died_philo_flag = true;
			printf("\033[0;35mphilosopher %d is dead. last meal %ld  current time %ld\x1B[0m\n", *data[i].philo_id, data[i].last_meal, gettime_ms(&data[i]));
			pthread_mutex_unlock(&data->rules->died_philo_mutex);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	*daily_schedule(void *a)
{
	t_philo_data	*data;

	data = a;
	while (!died_philo(data))
	{
		if (*data->philo_id % 2 == 0)
		{
			if (!red_flag(data))
				eating(data);
			else
			{
				while (red_flag(data))
				{
					// printf("this works? %d\n", *data->philo_id);
					eating(data);
				}
			}
			// while (red_flag(data) && !eating(data))
			// 	eating(data);
			sleep_think(data);
		}
		else if (*data->philo_id != data->rules->number_of_philos)
		{
			usleep(data->rules->eat_time);
			if (!red_flag(data))
				eating(data);
			else
			{
				while (red_flag(data))
					eating(data);
			}
			// while (red_flag(data) && !eating(data))
			// 	eating(data);
			sleep_think(data);
		}
	}
	free(data->philo_id);
	return (NULL);
}

void	set_the_table_and_do_stuff(t_philo_data *data)
{
	int i;

	i = 0;
	while (i <= data[0].rules->number_of_philos)
	{
		pthread_mutex_init(&data[i].meal_mutex, NULL);
		int *a = malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		if (i == 0)
			pthread_create(&(data[i].thread), NULL, &the_boss, &data);
		else
			pthread_create(&(data[i].thread), NULL, &daily_schedule, data + i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philo_data	*data;

	(void)argc;
	rules = malloc (sizeof(t_rules));
	if (!rules)
		return (0);
	rules_init(argv, rules);
	data = malloc (sizeof(t_philo_data) * (ft_atoi(argv[1]) + 1));
	if (!data)
		return (0);
	data_init(data, rules);
	set_the_table_and_do_stuff(data);
	clean_the_table(data);
	free_atexit(data, rules, ft_atoi(argv[1]));
}
