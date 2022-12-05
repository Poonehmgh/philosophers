/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:04:35 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/05 13:05:48 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

pthread_mutex_t global_lock;

time_t	gettime_ms(void)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000 + tmp.tv_usec * 0.001);
}

void	rules_init(char **argv, t_rules *rules)
{
	rules->die_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->think_time = ft_atoi(argv[5]);
	rules->number_of_philos = ft_atoi(argv[1]);
}

void data_init(t_philo_data *data, int philo_num)
{
	data = malloc(sizeof(t_philo_data) * philo_num);
	if (!data)
		return ;
	// data->forks = malloc(sizeof(t_fork));

}

void *boss(void *a)
{
	t_philo_data *data;
	data = *(t_philo_data **)a;
	int i; 
	i = 1;
	int num = data[1].rules->number_of_philos;
	while (i < num)
	{
		data[i].rules->time_left_to_die = data[i].rules->die_time + data[i].last_meal - gettime_ms() + data[i].rules->start_time;
		i++;
	}
	return (NULL);
}

// void	eating(t_philo_data *data)
// {
// 	// if (data->if_left_fork && data->if_right_fork)
// 	// {
// 	// 	pthread_mutex_lock(&data->right_fork);
// 	// 	printf("\033[0;31m%ld  ms: Philosopher %d took the right fork\033[0m\n",  gettime_ms() - data->rules->start_time, *data->philo_id);
// 	// 	pthread_mutex_lock(&data->left_fork);
// 	// 	printf("\033[0;31m%ld  ms: Philosopher %d took the left fork\033[0m\n",  gettime_ms() - data->rules->start_time, *data->philo_id);
// 	// 	usleep(data->rules->eat_time * 1000);
// 	// 	pthread_mutex_unlock(&data->left_fork);
// 	// 	pthread_mutex_unlock(&data->right_fork);
// 	// 	data->last_meal =  gettime_ms() - data->rules->start_time;
// 	// 	printf("%ld ms: Philosopher %d ended eating\n", gettime_ms() - data->rules->start_time , *data->philo_id);
// 	// }
// 	// data->if_left_fork = false;
// 	// data->if_right_fork = false;
// 	(void)data;
// }	
void *daily_schedule(void *a)
{
	t_philo_data *data;
	time_t time;
	data = (t_philo_data *)a;
	time = gettime_ms() - data->rules->start_time;
	eating(data);
	printf("%ld ms: Philosopher %d started sleeping\n", gettime_ms() - data->rules->start_time , *data->philo_id);
	usleep(data->rules->sleep_time * 1000);
	printf("%ld ms: Philosopher %d ended sleeping\n", gettime_ms() - data->rules->start_time , *data->philo_id);
	printf("%ld ms: Philosopher %d started thinking\n", gettime_ms() - data->rules->start_time , *data->philo_id);
	usleep(data->rules->think_time * 1000);
	printf("%ld ms: Philosopher %d ended thinking\n", gettime_ms() - data->rules->start_time , *data->philo_id);
	if (data->last_meal - data->rules->start_time >= data->rules->die_time)
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
	(void)argc;

	rules = malloc (sizeof(t_rules));
	if(!rules)
		return (0);
	rules->start_time = gettime_ms();
	pthread_mutex_init(&rules->mutex, NULL);
	rules_init(argv, rules);
	data = malloc (sizeof(t_philo_data) * (ft_atoi(argv[1]) + 1));
	int i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		data[i].rules = rules;
		t_fork *tmp = malloc(sizeof(t_fork));
		data[i].forks = *tmp;
		i++;
	}
	i = 0;
	// fork_initializaition(data);
	while (i <= ft_atoi(argv[1]))
	{
		int *a = malloc(sizeof(int));
		*a = i;
		data[i].philo_id = a;
		if (i == data->rules->number_of_philos)
			pthread_create(&(data[i].thread), NULL, &boss, &data);
		else
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
