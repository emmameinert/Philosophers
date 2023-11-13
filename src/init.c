/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:59:32 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:47:58 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_philo	*init_philo(int count)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(*philo) * (count + 1));
	if (!philo)
		return (NULL);
	return (philo);
}

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof((*data)) * 1);
	if (!data)
		return (NULL);
	data->philo_nb = ft_atol(argv[1]);
	data->philo = init_philo(data->philo_nb);
	init_mutex(data);
	return (data);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data->printing), NULL) != 0)
	{
		printf("Error mutex init\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->eating_count_lock), NULL) != 0)
	{
		printf("Error mutex init\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->death_lock), NULL) != 0)
	{
		printf("Error mutex init\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->routine_lock), NULL) != 0)
	{
		printf("Error mutex init\n");
		return (1);
	}
	return (0);
}
