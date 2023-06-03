#include "philo.h"

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

void    eat_routine(t_philo *philo)
{
    t_philo *temp;

    temp = (t_philo *)philo;
    pthread_mutex_lock(&(temp->data->left_fork));
    print_message((temp->data), time_diff(temp->data->start_time), temp->id, 'f');
    pthread_mutex_lock(&(temp->data->right_fork));
    print_message((temp->data), time_diff(temp->data->start_time), temp->id, 'f');
    temp->last_meal = time_diff(temp->data->start_time);
    print_message((temp->data), temp->last_meal, temp->id, 'e');
    pthread_mutex_lock(&(temp->eating_mutex));
    temp->data->eating_count++;
    pthread_mutex_unlock(&(temp->eating_mutex));
    temp->sleep_start = time_diff(temp->data->start_time);
    print_message((temp->data), temp->sleep_start, temp->id, 's');
    my_sleep(philo); 
    pthread_mutex_unlock(&(temp->data->left_fork));
    pthread_mutex_unlock(&(temp->data->right_fork));
}

void*    routine(void *philo)
{
    t_philo *temp;
    int i;

    i = 0;
    temp = (t_philo *)philo;
    if ((temp->id % 2) == 0)
        usleep(1500);
    while (!death_check(&temp)) //i < temp->data->philo_nb && 
    {
        eat_routine(temp);
        if (comp_eat_count(temp) == 1)
        {
            stop_routine(philo);
            return (NULL);
        }
        print_message((temp->data), time_diff(temp->data->start_time), temp->id, 's');
        my_sleep(temp);
        print_message((temp->data), time_diff(temp->data->start_time), temp->id, 't');
        //i++;
    }
    return (NULL);
}

void    stop_routine(t_philo **philo)
{
    int i;

    i = 0;
    while (i < (*philo)->data->philo_nb)
    {
        if (pthread_join(philo[i]->ph_thread, NULL) != 0)
            return ;
        i++;
    }
    pthread_mutex_destroy(&((*philo)->data->left_fork));
    pthread_mutex_destroy(&((*philo)->data->right_fork));
    pthread_mutex_destroy(&((*philo)->data->printing));
    pthread_mutex_destroy(&((*philo)->data->eating_count_lock));
    pthread_mutex_destroy(&((*philo)->data->death_lock));
}

void    start_routine(t_philo **philo)
{
    int i;

    i = 0;
    pthread_mutex_lock(&((*philo)->data->eating_lock));
    (*philo)->data->eating_count = 0; 
    while (i < (*philo)->data->philo_nb)
    {
        philo[i]->id = i + 1;
        //printf("%d\n", philo[i]->id);
        if (pthread_create(&(philo[i]->ph_thread), NULL, &routine, philo[i]) != 0) 
        {
            printf("Error with thread creation \n");
            return ;
        }
        i++;   
    }
    death_check(philo);
    stop_routine(philo);
    pthread_mutex_unlock(&((*philo)->data->eating_lock));
}

//what happens with one philosopher edge case

