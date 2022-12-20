/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:44:18 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/20 20:11:48 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

void	red(void)
{
	printf("\033[1;31m");
}

void	yellow(void)
{
	printf("\033[1;33m");
}

void	green(void)
{
	printf("\033[0;32m");
}

void	white(void)
{
	printf("\033[0m");
}

char	*dinner(int i)
{
	char	*s[9];

	s[0] = "Ghorme Sabzi.";
	s[1] = "Big Mac.";
	s[2] = "Pizza.";
	s[3] = "Adas Polo.";
	s[4] = "Pasta Chicken Alfredo.";
	s[5] = "Bratwurst.";
	s[6] = "Soup.";
	s[7] = "Noon Barbari.";
	s[8] = "Abgoosht.";
	return (s[i]);
}
