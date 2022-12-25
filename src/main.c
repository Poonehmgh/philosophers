/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/25 16:09:02 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	*daily_routine(void *a)
{
	t_philo_data	*data;

	data = a;
	if (*data->philo_id % 2)
		usleep(500 * data->rules->eat_time);
	while (!died_philo(data))
	{
		if (*data->philo_id == data->rules->number_of_philos
			&& data->rules->number_of_philos == 1)
			sleep_think(data);
		if (!eating(data))
			break ;
		sleep_think(data);
	}
	free(data->philo_id);
	return (NULL);
}

void	init_mutexes(t_philo_data *data)
{
	int	i;

	i = 1;
	while (i <= data->rules->number_of_philos)
	{
		pthread_mutex_init(&data->rules->forks[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->rules->died_philo_mutex, NULL);
	pthread_mutex_init(&data->rules->ate_min_meal, NULL);
	pthread_mutex_init(&data->rules->printing, NULL);
}

void	set_the_table_and_do_stuff(t_philo_data *data)
{
	int	i;
	int	*a;

	i = 0;
	init_mutexes(data);
	while (i <= data->rules->number_of_philos)
	{
		pthread_mutex_init(&data[i].meal_mutex, NULL);
		i++;
	}
	i = 0;
	while (i <= data[0].rules->number_of_philos)
	{
		a = malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		if (i == 0)
		{
			pthread_create(&(data[i].thread), NULL, &table, &data);
			free(a);
		}
		else
			pthread_create(&(data[i].thread), NULL, &daily_routine, data + i);
		i++;
	}
}

void	input_validity(int argc, char **argv)
{
	int	i;

	if (argc != 6 && argc != 5)
		err("\nError: invalid number of arguments.\n\n");
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			err("\nError: input not valid.\n\n");
		i++;
	}
	if (ft_atoi(argv[2]) < ft_atoi(argv[3]) + ft_atoi(argv[4]))
		err("\nError: Time to die must be > time to eat + time to sleep.\n\n");
	arg_check(argv);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philo_data	*data;

	input_validity(argc, argv);
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
}
