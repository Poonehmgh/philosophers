/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:44:18 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/12/20 14:45:56 by pmoghadd         ###   ########.fr       */
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
	char	*s[9] = {
		"Ghorme Sabzi.",
		"Big Mac.",
		"Pizza.",
		"Adas Polo.",
		"Pasta with Pesto Sause.",
		"Bratwurst.",
		"Soup.",
		"Aash.",
		"Noon Barbari."
	};

	return (s[i]);
}
