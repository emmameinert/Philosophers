/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:44:03 by emeinert          #+#    #+#             */
/*   Updated: 2023/06/21 21:14:09 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_data **data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (flag == 0)
	{
		i = 0;
		while (i < (*data)->philo_nb)
		{
			if (life_status(&((*data)->philo[i])) == 2)
				flag = 1;
			if (time_diff(get_time(), (*data)->start_time) \
					>= (*data)->philo->time_to_die)
			{
				if ((death_check(&(*data)->philo[i]) == 1)
					|| life_status(&((*data)->philo[i])) == 2)
					flag = 1;
			}
			i++;
		}
	}
	join_mutex(*data);
	return ;
}

void	join_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philo[i].ph_thread, NULL))
		{
			printf("detach error with: %d", (data)->philo[i].id);
			break ;
		}
		i++;
	}
}

void	one_philo(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock((philo->left_fork));
	print_message((philo->data), time_diff(get_time(), \
				philo->data->start_time), philo->id, 'f');
	time = get_time();
	while (42)
	{
		usleep(300);
		if (time_diff(get_time(), time) >= philo->time_to_die)
			break ;
	}
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_lock(&(philo->data->death_lock));
	philo->data->death_flag = 1;
	pthread_mutex_unlock(&(philo->data->death_lock));
	return ;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("Error with number of arguments\n");
		return (0);
	}
	if (check_input(argc, argv) == 1)
		return (0);
	data = init_data(argv);
	if (data == NULL)
		return (0);
	parsing(&data, argv);
	start_routine(&data);
	monitoring(&data);
	destroy_mutex(data);
	free(data->fork);
	free(data->philo);
	free(data);
	return (0);
}
