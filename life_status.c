#include "philo.h"

int life_status(t_philo **philo)
{
    int i;

    i = 0;
    if (death_check(philo) == 1)
    {
        //printf("dead\n");
        return (1);
    }
    //printf("last meal: %d %lld\n", (*philo)[i].id, (*philo)[i].last_meal);
    if (comp_eat_count(philo) == 1) //if its one that one has to stop eating 
    {
        pthread_mutex_lock(&((*philo)->data->eating_count_lock));
        (*philo)->data->general_eating_count++;
        if ((*philo)->data->general_eating_count == ((*philo)->data->philo_nb))
        {
            pthread_mutex_unlock(&((*philo)->data->eating_count_lock));
            printf(" %d eaten enough \n", (*philo)->id);
            return (1);
        }
        pthread_mutex_unlock(&((*philo)->data->eating_count_lock));
        return (0);
    }
    return (0);
}

int death_check(t_philo **philo)
{
    pthread_mutex_lock(&((*philo)->data->death_lock)); //das hier ist faulty
    if (((*philo)->last_meal > 0) && (time_diff((*philo)->last_meal, (*philo)->data->start_time) > (*philo)->time_to_die)) // update start->time to old time to update the toimes throughout the program
    {
        print_message((*philo)->data, time_diff(get_time(), (*philo)->data->start_time), (*philo)->id, 'd');
        pthread_mutex_unlock(&((*philo)->data->death_lock));
        return (1);
    }
    pthread_mutex_unlock(&((*philo)->data->death_lock));
    return (0);
}

int   comp_eat_count(t_philo **philo) 
{
    pthread_mutex_lock(&((*philo)->eating_mutex)); 
    if ((*philo)->data->not_each_philo_must_eat < 0)
    {
        pthread_mutex_lock(&((*philo)->eating_mutex));
        return (0);
    }
    else if ((*philo)->own_eating_count < (*philo)->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&((*philo)->eating_mutex));
        return (0);
    }
    else if ((*philo)->own_eating_count == (*philo)->data->not_each_philo_must_eat)
    {
        pthread_mutex_unlock(&((*philo)->eating_mutex));
        return (1);
    }
    return (0);
}