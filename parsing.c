/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhewong <zhewong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:26:38 by zhewong           #+#    #+#             */
/*   Updated: 2024/10/22 10:26:40 by zhewong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while(is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Positive values only");
	if (!is_digit(*str))
		error_exit("Invalid input");
	num = str;
	while (is_digit(*str++))
		++len;
	if (len > INT_MAX)
		error_exit("Integer overflow");
	return (num);
}

static long	ft_atol(const char *str)
{
	long	num;
	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		error_exit("Integer overflow");
	return (num);
}

/* ./philo 5 800 200 200 [5]
make sure: actual nums, not>INT_MAX, timestamps>60ms */
void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("use timestamps bigger than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}