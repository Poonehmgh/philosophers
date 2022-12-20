/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/20 15:19:16 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	*daily_routine(void *a)
{
	t_philo_data	*data;

	data = a;
	while (!died_philo(data))
	{
		if (*data->philo_id % 2 && !died_philo(data))
			sleep_think(data);
		while (!eating(data) && !died_philo(data))
		{
			if (eating(data))
				break ;
		}
		if (*data->philo_id % 2 == 0 && !died_philo(data))
			sleep_think(data);
	}
	free(data->philo_id);
	return (NULL);
}

void	set_the_table_and_do_stuff(t_philo_data *data)
{
	int	i;
	int	*a;

	i = 0;
	while (i <= data[0].rules->number_of_philos)
	{
		pthread_mutex_init(&data[i].meal_mutex, NULL);
		a = malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		if (i % 2)
			usleep(50);
		if (i == 0)
			pthread_create(&(data[i].thread), NULL, &table, &data);
		else
			pthread_create(&(data[i].thread), NULL, &daily_routine, data + i);
		i++;
	}
}

void	input_validity(int argc, char **argv)
{
	int	i;

	if (argc != 6 && argc != 5)
	{
		perror("Error: input not valid.");
		exit(0);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: input not valid.\n");
			exit(0);
		}
		i++;
	}
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
	free_atexit(data, rules, ft_atoi(argv[1]));
}
