/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/03 19:51:36 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

pthread_mutex_t global_lock;

void	rules_init(char **argv, t_rules *rules)
{
	rules->die_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->think_time = ft_atoi(argv[5]);
}

void data_init(t_philo_data *data, int philo_num)
{
	data = malloc(sizeof(t_philo_data) * philo_num);
	if (!data)
		return ;
}

void *boss(t_philo_data *data)
{
	printf("hi%d\n", *data->philo_id);
	return (NULL);
}

void *daily_schedule(void *a)
{
	t_philo_data *data;
	struct timeval		tmp;
	int time;
	gettimeofday(&tmp, NULL);
	data = (t_philo_data *)a;
	time = -(*data->rules).run_time.tv_usec + tmp.tv_usec;
	if (*data->philo_id == 0)
		return (boss(data));
	printf("\033[0;31m%d  ms: Philosopher %d started eating\033[0m\n", time , *data->philo_id);
	usleep(data->rules->eat_time * 1000);
	printf("%d ms: Philosopher %d ended eating\n", time , *data->philo_id);
	printf("%d ms: Philosopher %d started sleeping\n", time , *data->philo_id);
	usleep(data->rules->sleep_time * 1000);
	printf("%d ms: Philosopher %d ended sleeping\n", time , *data->philo_id);
	printf("%d ms: Philosopher %d started thinking\n", time , *data->philo_id);
	usleep(data->rules->think_time * 1000);
	printf("%d ms: Philosopher %d ended thinking\n", time , *data->philo_id);
	if (time >= data->rules->die_time * 1000)
		printf("philosopher %d is dead.\n", *data->philo_id);
		
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
	struct timeval		tmp;
	gettimeofday(&tmp, NULL);
	(void)argc;
	// printf("time %f   \n", tmp.tv_usec * 0.001);
	rules = malloc (sizeof(t_rules));
	if(!rules)
		return (0);
	rules->run_time = tmp;
	pthread_mutex_init(&rules->mutex, NULL);
	rules_init(argv, rules);
	data = malloc (sizeof(t_philo_data) * (ft_atoi(argv[1] + 1)));
	int i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		data[i].rules = rules;
		i++;
	}
	i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		int *a=malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		pthread_create(&(data[i].thread), NULL, &daily_schedule, data + i);
		i++;
	}
	i = 0;
	while(i <= ft_atoi(argv[1]))
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&rules->mutex);
	free_atexit(data, rules, ft_atoi(argv[1]));
}
