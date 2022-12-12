/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/12 01:01:36 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

time_t	gettime_ms(t_philo_data *data)
{
	struct timeval tmp;
	pthread_mutex_lock(&data->rules->time_stamp);
	gettimeofday(&tmp, NULL);
	time_t res = tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	pthread_mutex_unlock(&data->rules->time_stamp);
	return (res - data->rules->start_time);
}

void	rules_init(char **argv, t_rules *rules)
{
	
	struct timeval t;
	gettimeofday(&t, NULL);
	rules->start_time = t.tv_sec * 1000 + t.tv_usec * 0.001;
	rules->die_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->think_time = ft_atoi(argv[5]);
	rules->number_of_philos = ft_atoi(argv[1]);
	rules->min_meals = ft_atoi(argv[6]);
	rules->forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
	rules->died_philo_flag = false;
	int i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		rules->forks[i].availability = true;
		i++;
	}
}

void data_init(t_philo_data *data, t_rules *rules)
{
	int i = 0;
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
		if (!died_philo(data) && data[i].number_of_meals == data->rules->min_meals)
		{
			printf("philosopher %d has eaten enough!\n", i);
			pthread_detach(data[i].thread);
		}
		i++;
	}
	return (NULL);
}

void *daily_schedule(void *a)
{
	t_philo_data	*data;

	data = a;
	while (!died_philo(data))
	{
		eating(data);
		sleep_think(data);
	}
	free(data->philo_id);
	return (NULL);
}

void	free_atexit(t_philo_data *data, t_rules *rules, int num_philos)
{
	int i;

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

void clean_the_table(t_philo_data *data)
{
	int i;

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

void set_the_table_and_do_stuff(t_philo_data *data)
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

int main (int argc, char **argv)
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
