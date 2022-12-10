/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/10 16:19:41 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"


pthread_mutex_t global_lock;

time_t	gettime_ms(t_philo_data *data)
{
	struct timeval tmp;
	pthread_mutex_lock(&global_lock);
	gettimeofday(&tmp, NULL);
	time_t res = tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	pthread_mutex_unlock(&global_lock);
	return (res - data->rules->start_time);
}

void	rules_init(char **argv, t_rules *rules)
{
	rules->die_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->think_time = ft_atoi(argv[5]);
	rules->number_of_philos = ft_atoi(argv[1]);
	rules->min_meals = ft_atoi(argv[6]);
	rules->forks = malloc(sizeof(t_fork) * ft_atoi(argv[2]));
	rules->died_philo_flag = false;
	int i = 0;
	while (i < ft_atoi(argv[1]))
	{
		// if (i % 2 == 0)
			rules->forks[i].availability = true;
		// else
		// 	rules->forks[i].availability = false;
		i++;
	}
}

void data_init(t_philo_data *data, int philo_num)
{
	data = malloc(sizeof(t_philo_data) * philo_num);
	if (!data)
		return ;
	// data->forks = malloc(sizeof(t_fork));
	int i = 0;
	while (i < philo_num)
	{
		data[i].last_meal = -1;
		data[i].number_of_meals = 0;
		i++;
	}

}

void *boss(void *a)
{
	t_philo_data	*data;
	int				i;

	data = *(t_philo_data **)a;
	i = 1;
	int num = data[1].rules->number_of_philos;
	while (i <= num && !data->rules->died_philo_flag) 
	{
		if (i == num)
			i = 1;
		if (data[i].last_meal + data[i].rules->die_time - gettime_ms(&data[i]) >= data[i].rules->eat_time && data[i].last_meal + data[i].rules->die_time - gettime_ms(&data[i]) <= 2 * data[i].rules->eat_time)
			{
				// printf("from the infinite loop: %ld\n", data[i].last_meal + data[i].rules->die_time - gettime_ms(&data[i]));
			eating(data + i);}
		else
			sleep_think(data + i);
		if (data[i].last_meal + data[i].rules->die_time - gettime_ms(&data[i]) < data[i].rules->eat_time)
		{
			pthread_mutex_lock(&data->rules->died_philo_mutex);
			data->rules->died_philo_flag = true;
			pthread_mutex_unlock(&data->rules->died_philo_mutex);
			printf(" \033[0;35mphilosopher %d is dead. last meal %ld  current time %ld\x1B[0m\n", *data->philo_id, data->last_meal, gettime_ms(&data[i]));	
			return (NULL);
		}
		if (!data->rules->died_philo_flag && data[i].number_of_meals == data->rules->min_meals)
		{
			printf("philosopher %d has eaten enough!\n", i);
			// pthread_detach(data[i].thread);
		}
		i++;
	}
	return (NULL);
}

void *daily_schedule(void *a)
{
	t_philo_data *data;
	time_t time;
	data = (t_philo_data *)a;
	time = gettime_ms(data) - data->rules->start_time;
	int i = 0;
	while (!data->rules->died_philo_flag && i < data->rules->min_meals)
	{
		eating(data);
		sleep_think(data);
		i++;
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

int main (int argc, char **argv)
{
	t_rules			*rules;
	t_philo_data 	*data;
	(void)argc;

	rules = malloc (sizeof(t_rules));
	if(!rules)
		return (0);
	struct timeval tmp;
	pthread_mutex_lock(&global_lock);
	gettimeofday(&tmp, NULL);
	rules->start_time = tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	pthread_mutex_init(&rules->mutex, NULL);
	rules_init(argv, rules);
	data = malloc (sizeof(t_philo_data) * (ft_atoi(argv[1]) + 1));
	int i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		data[i].rules = rules;
		i++;
	}
	i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		int *a = malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		if (i == 0)
			pthread_create(&(data[i].thread), NULL, &boss, &data);
		else
			pthread_create(&(data[i].thread), NULL, &daily_schedule, data + i);
		i++;
	}
	i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&rules->mutex);
	free_atexit(data, rules, ft_atoi(argv[1]));
}
