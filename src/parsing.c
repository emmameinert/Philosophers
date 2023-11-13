/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:51:46 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:48:14 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_forks(t_data **data)
{
	int	i;

	i = -1;
	(*data)->fork = malloc(sizeof(pthread_mutex_t) * ((*data)->philo_nb));
	if (!(*data)->fork)
		return ;
	while (++i < (*data)->philo_nb)
	{
		pthread_mutex_init(&((*data)->fork[i]), NULL);
	}
	i = 0;
	while (i < (*data)->philo_nb)
	{
		if (i == (*data)->philo_nb - 1)
		{
			(*data)->philo[i].left_fork = &(*data)->fork[i];
			(*data)->philo[i].right_fork = (*data)->philo[0].left_fork;
		}
		else
		{
			(*data)->philo[i].left_fork = &(*data)->fork[i];
			(*data)->philo[i].right_fork = &(*data)->fork[i + 1];
		}
		i++;
	}
}

void	parsing(t_data **data, char **argv)
{
	int	i;

	i = -1;
	(*data)->general_eating_count = 0;
	(*data)->death_flag = 0;
	while (++i < (*data)->philo_nb)
	{
		(*data)->philo[i].data = (*data);
		(*data)->philo[i].time_to_die = ft_atol(argv[2]);
		(*data)->philo[i].time_to_eat = ft_atol(argv[3]);
		(*data)->philo[i].time_to_sleep = ft_atol(argv[4]);
		(*data)->philo[i].own_eating_count = 0;
		(*data)->philo[i].last_meal = 0;
		(*data)->philo[i].eating_flag = 0;
		(*data)->philo[i].left_fork = NULL;
		(*data)->philo[i].right_fork = NULL;
		pthread_mutex_init(&((*data)->philo[i].eating_mutex), NULL);
	}
	if (argv[5])
		(*data)->not_each_philo_must_eat = ft_atol(argv[5]);
	else
		(*data)->not_each_philo_must_eat = -1;
	init_forks(data);
}
