/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:04:19 by emeinert          #+#    #+#             */
/*   Updated: 2023/06/22 10:48:37 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	int	answer;

	answer = 0;
	if (c >= 48 && c <= 57)
		answer = 1;
	else
		answer = 0;
	return (answer);
}

static int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_is_negative(char c)
{
	if (c == '-')
		return (1);
	else
		return (0);
}

static int	ft_check_eating(char *argv)
{
	if (ft_atol(argv) == 0)
	{
		printf("Error: number is wrong:%s\n", argv);
		return (1);
	}
	if (ft_atol(argv) > 2147483647 || ft_atol(argv) < -2147483648)
	{
		printf("Error: number is too big: %s\n", argv);
		return (1);
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < (argc))
	{
		if (ft_is_negative(argv[i][0]) || ft_is_number(argv[i]))
			return (1);
	}
	if (ft_atol(argv[1]) > 200 || ft_atol(argv[1]) == 0)
	{
		printf("Error: wrong amount of Philosophers\n");
		return (1);
	}
	if ((ft_atol(argv[2]) < 60) || (ft_atol(argv[3]) < 60)
		|| (ft_atol(argv[4]) < 60))
	{
		printf("Error: time must be between 60 and INTMAX \n");
		return (1);
	}
	if (ft_check_eating(argv[2]) == 1 || ft_check_eating(argv[2]) == 1
		|| ft_check_eating(argv[2]) == 1)
		return (1);
	if (argv[5] && ft_check_eating(argv[5]) == 1)
		return (1);
	return (0);
}
