/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:24:48 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/25 11:46:46 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	err(char *s)
{
	red();
	printf("%s", s);
	exit(0);
}

void	arg_check(char **argv)
{
	int	i;

	i = 2;
	if (ft_atoi(argv[1]) > 300)
		err("\nError: number of philosophers should be less than 300.\n\n");
	while (i < 5)
	{
		if (10000 < ft_atoi(argv[i]) || ft_atoi(argv[i]) < 60)
			err("\nError: Invalid time, should be <= 10000 and >= 60 ms.\n\n");
		i++;
	}
}
