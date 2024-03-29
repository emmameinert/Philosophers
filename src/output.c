/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:48:57 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:48:12 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	print_message(t_data *data, time_t time, int id, char message)
{
	pthread_mutex_lock(&data->printing);
	if (death_check(&(data->philo[id - 1])) == 1
		|| life_status(&(data->philo[id - 1])) == 2)
	{
		pthread_mutex_unlock(&data->printing);
		return (1);
	}
	if (message == 'f')
	{
		printf("%s%ld %d %s", YELLOW, time, id, "has taken a fork\n");
	}
	else if (message == 'e')
	{
		printf("%s%ld %d %s", BYELLOW, time, id, "is eating\n");
	}
	else if (message == 's')
	{
		printf("%s%ld %d %s", NC, time, id, "is sleeping\n");
	}
	else if (message == 't')
	{
		printf("%s%ld %d %s", GREEN, time, id, "is thinking\n");
	}
	pthread_mutex_unlock(&data->printing);
	return (0);
}
