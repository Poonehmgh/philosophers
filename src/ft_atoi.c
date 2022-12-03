/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:33:47 by pooneh            #+#    #+#             */
/*   Updated: 2022/12/01 15:41:42 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

int	charnumeric(char c)
{
	return (c >= '0' && c <= '9');
}

int	str_to_nbr(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (charnumeric(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

int	check_sign(char *str, int *result)
{
	int	i;

	i = 0;
	*result = 1;
	if (!charnumeric(str[i]))
	{
		if (str[i] == '-')
			*result = -1 * *result;
		else if (str[i] != '+')
			return (-5);
		i++;
	}
	return (i);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		index;
	int		tmp;
	char	*tstr;

	tstr = (char *)str;
	index = skip_spaces(tstr);
	tmp = check_sign(tstr + index, &sign);
	if (tmp == -5)
		return (0);
	index = tmp + index;
	return (sign * str_to_nbr(tstr + index));
}