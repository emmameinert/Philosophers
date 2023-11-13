/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:11:39 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:48:53 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static long long	ft_check(const char *str, int i, long sign, long result)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			result = 0;
		result = result * 10 + (str[i] - '0');
		i++;
		if (sign * result > 2147483647)
			return (-2147483649);
		if (sign * result < -2147483648)
			return (-21474836489);
	}
	return (sign * result);
}

long long	ft_atol(const char *str)
{
	long	i;
	long	result;
	long	sign;

	result = 2147483648;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (!ft_isdigit(str[i]))
			return (result);
	}
	result = ft_check(str, i, sign, result);
	return (result);
}

int	my_sleep(time_t count, t_philo **philo)
{
	long long	time;

	time = get_time();
	while (death_check(*philo) == 0)
	{
		usleep(300);
		if (time_diff(get_time(), time) >= count)
			return (0);
	}
	return (1);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (&(data->fork[i]))
			pthread_mutex_destroy(&data->fork[i]);
		if (&(data->philo[i].eating_mutex))
			pthread_mutex_destroy(&data->philo[i].eating_mutex);
		i++;
	}
	if (&(data->printing))
		pthread_mutex_destroy(&(data->printing));
	if (&(data->eating_count_lock))
		pthread_mutex_destroy(&(data->eating_count_lock));
	if (&(data->death_lock))
		pthread_mutex_destroy(&(data->death_lock));
	if (&(data->routine_lock))
		pthread_mutex_destroy(&(data->routine_lock));
}
