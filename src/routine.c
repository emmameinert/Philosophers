/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:14:36 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:48:48 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	take_forks(t_philo **philo)
{
	if ((death_check(*philo)) == 0 && life_status((*philo)) < 2)
	{
		pthread_mutex_lock(((*philo)->left_fork));
		if (print_message(((*philo)->data), time_diff(get_time(), \
						(*philo)->data->start_time), (*philo)->id, 'f') == 1)
		{
			pthread_mutex_unlock(((*philo)->left_fork));
			return (1);
		}
		pthread_mutex_lock(((*philo)->right_fork));
		if (print_message(((*philo)->data), time_diff(get_time(), \
						(*philo)->data->start_time), (*philo)->id, 'f') == 1)
		{
			pthread_mutex_unlock(((*philo)->right_fork));
			pthread_mutex_unlock(((*philo)->left_fork));
			return (1);
		}
		return (0);
	}
	return (1);
}

int	eat_routine(t_philo *philo)
{
	if (take_forks(&philo) == 1)
		return (1);
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->own_eating_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->eating_mutex));
	if (print_message(philo->data, time_diff(philo->last_meal, \
					philo->data->start_time), philo->id, 'e') == 1)
	{
		pthread_mutex_unlock((philo->right_fork));
		pthread_mutex_unlock((philo->left_fork));
		return (1);
	}
	if (my_sleep(philo->time_to_eat, &philo) == 1)
	{
		pthread_mutex_unlock((philo->right_fork));
		pthread_mutex_unlock((philo->left_fork));
		return (1);
	}
	pthread_mutex_unlock((philo->right_fork));
	pthread_mutex_unlock((philo->left_fork));
	return (0);
}

int	call_routine(t_philo *temp)
{
	if (temp->data->philo_nb > 1 && ((temp->id % 2) == 0
			|| temp->id == temp->data->philo_nb))
	{
		if (print_message((temp->data), time_diff(get_time(), \
						temp->data->start_time), temp->id, 't') == 1)
			return (1);
		if (my_sleep(temp->time_to_eat, &temp) == 1)
			return (1);
	}
	while (temp->eating_flag == 0)
	{
		if (eat_routine(temp) == 1)
			return (1);
		if (print_message((temp->data), time_diff(get_time(), \
						temp->data->start_time), temp->id, 's') == 1)
			return (1);
		if (my_sleep(temp->time_to_sleep, &temp) == 1)
			return (1);
		if (print_message((temp->data), time_diff(get_time(), \
						temp->data->start_time), temp->id, 't') == 1)
			return (1);
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*temp;

	temp = (t_philo *)philo;
	pthread_mutex_lock(&(temp->data->routine_lock));
	temp->last_meal = temp->data->start_time;
	pthread_mutex_unlock(&(temp->data->routine_lock));
	if (temp->data->philo_nb == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (call_routine(temp) == 1)
		return (NULL);
	return (NULL);
}

int	start_routine(t_data **data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&((*data)->routine_lock));
	while (i < (*data)->philo_nb)
	{
		(*data)->philo[i].id = i + 1;
		if (pthread_create(&((*data)->philo[i].ph_thread), \
					NULL, &routine, &(*data)->philo[i]) != 0)
		{
			pthread_mutex_unlock(&((*data)->routine_lock));
			return (1);
		}
		i++;
	}
	(*data)->start_time = get_time();
	pthread_mutex_unlock(&((*data)->routine_lock));
	return (0);
}
