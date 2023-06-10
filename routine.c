#include "philo.h"

void    eat_routine(t_philo *philo)
{
    t_philo *temp;
    t_data *data;

    temp = (t_philo *)philo;
    data = temp->data;
    pthread_mutex_lock((temp->left_fork));
    print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 'f');
    pthread_mutex_lock((temp->right_fork));
    print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 'f');
    temp->last_meal = time_diff(get_time(), temp->data->start_time);
    print_message((temp->data), temp->last_meal, temp->id, 'e');
    pthread_mutex_lock(&(temp->eating_mutex)); 
    temp->data->eating_count++;
    pthread_mutex_unlock(&(temp->eating_mutex));
    temp->sleep_start = time_diff(get_time(), temp->data->start_time);
    print_message((temp->data), temp->sleep_start, temp->id, 's');
    my_sleep(temp->time_to_sleep); 
    pthread_mutex_unlock((temp->left_fork));
    pthread_mutex_unlock((temp->right_fork));
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
    i = 0;
    while (i < (*philo)->data->philo_nb)
    {
        pthread_mutex_destroy(&((*philo)->data->fork[i]));
    }
    pthread_mutex_destroy(&((*philo)->data->printing));
    pthread_mutex_destroy(&((*philo)->data->eating_count_lock));
    pthread_mutex_destroy(&((*philo)->data->death_lock));
}


void*   routine(void *philo)
{
    t_philo *temp;
    int i;

    i = 0;
    temp = (t_philo *)philo;
    if ((temp->id % 2) == 0)
        usleep(1500);
    while (!life_status(&temp))
    {
        eat_routine(temp);
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 't');
    }
    printf("%ld\n", temp[i].last_meal);
    return (NULL);
}

void    start_routine(t_philo **philo)
{
    int i;
    i = 0;
    pthread_mutex_lock(&((*philo)->data->routine_lock));
    (*philo)->data->eating_count = 0;
    while (i < (*philo)->data->philo_nb)
    {
        philo[i]->id = i + 1;
        if (pthread_create(&(philo[i]->ph_thread), NULL, &routine, philo[i]) != 0) 
        {
            printf("Error with thread creation \n");
            return ;
        }
        i++;   
    }//ggf nochmal life_status checken
    stop_routine(philo);
    pthread_mutex_unlock(&((*philo)->data->routine_lock));
}