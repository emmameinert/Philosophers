/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:07:59 by emeinert          #+#    #+#             */
/*   Updated: 2023/06/20 21:44:48 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int life_status(t_philo *philo)
{
    if (comp_eat_count(philo) == 1)
    {
        pthread_mutex_lock(&(philo->data->eating_count_lock));
        philo->data->general_eating_count++;
        if (philo->data->general_eating_count == (philo->data->philo_nb))
        {
            pthread_mutex_unlock(&(philo->data->eating_count_lock));
            return (1);
        }
        pthread_mutex_unlock(&(philo->data->eating_count_lock));
        return (2);
    }
    return (0);
}

int death_check(t_philo *philo) //maybe make two seperate functions so data races stop here, could send a flag
{
    pthread_mutex_lock(&(philo->data->death_lock));
    if (philo->data->philo_nb > 1 && (philo->data->death_flag) == 1)
    {
        pthread_mutex_unlock(&(philo->data->death_lock));
        return (1);
    }
    pthread_mutex_unlock(&(philo->data->death_lock));
    pthread_mutex_lock(&(philo->eating_mutex));
    if ((time_diff(get_time(), philo->last_meal) >= philo->time_to_die))
    {
        pthread_mutex_unlock(&(philo->eating_mutex));
        printf("%s%lld %d died\n", RED, time_diff(get_time(), philo->data->start_time), philo->id);
        pthread_mutex_lock(&(philo->data->death_lock));
        philo->data->death_flag = 1;
        pthread_mutex_unlock(&(philo->data->death_lock));
        return (1);
    }
    pthread_mutex_unlock(&(philo->eating_mutex));
    return (0);
}


int   comp_eat_count(t_philo *philo)
{
    pthread_mutex_lock(&(philo->eating_mutex));
    if (philo->data->not_each_philo_must_eat < 0)
    {
        pthread_mutex_unlock(&(philo->eating_mutex));
        return (0);
    }
    else if (philo->own_eating_count < philo->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&(philo->eating_mutex));
        return (0);
    }
    else if (philo->own_eating_count >= philo->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&(philo->eating_mutex));
        return (1);
    }
    return (0);
}
