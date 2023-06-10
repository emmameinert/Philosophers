#include "philo.h"

int life_status(t_philo **philo)
{
    int i;

    i = 0;
    while (i < (*philo)->data->philo_nb)
    {
        if (death_check(philo[i]))
            return (1);
        if (comp_eat_count(philo[i]))
            return (1);
        i++;
    }
    return (0);
}

int death_check(t_philo *philo)
{

    pthread_mutex_lock(&(philo->data->death_lock));
    if ((philo->last_meal > 0) && (time_diff(get_time(), philo->last_meal) > philo->time_to_die)) 
    {
        print_message((philo->data), time_diff(get_time(), philo->data->start_time), philo->id, 'd');
        pthread_mutex_unlock(&(philo->data->death_lock));
        return (1);
    }
    pthread_mutex_unlock(&(philo->data->death_lock));
    return (0);
}

int   comp_eat_count(t_philo *philo) 
{
    pthread_mutex_lock(&(philo->data->eating_count_lock));
    if (philo->data->not_each_philo_must_eat < 0)
    {
        pthread_mutex_unlock(&(philo->data->eating_count_lock));
        return (0);
    }
    else if (philo->data->eating_count < philo->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&(philo->data->eating_count_lock));
        return (0);
    }
    else if (philo->data->eating_count == philo->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&(philo->data->eating_count_lock));
        return (1);
    }
    return (0);
}