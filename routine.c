#include "philo.h"

// void    waiting(t_philo *philo)
// {
//     long time;

//     time = get_time();
//     while (!life_status(philo))
//     {
//         if (time_diff(time, philo->last_meal) >= philo->time_to_eat)
//            break ;
//         usleep(50);
//     }
// }

void    eat_routine(t_philo *philo)
{
    pthread_mutex_lock((philo->left_fork));
    print_message((philo->data), time_diff(get_time(), philo->data->start_time), philo->id, 'f');
    pthread_mutex_lock((philo->right_fork));
    print_message((philo->data), time_diff(get_time(),philo->data->start_time), philo->id, 'f');
    philo->old_time = get_time(); 
    print_message(philo->data, time_diff(philo->old_time, philo->data->start_time), philo->id, 'e');
    if (my_sleep(philo->time_to_eat, &philo) != 0) 
    {
        printf("hello there %d\n", philo->id);
        pthread_mutex_unlock((philo->left_fork));
        pthread_mutex_unlock((philo->right_fork));
        return ;
    }
    pthread_mutex_unlock((philo->left_fork));
    pthread_mutex_unlock((philo->right_fork));
    philo->last_meal = time_diff(get_time(), philo->old_time);//nochmal angucke n
    pthread_mutex_lock(&(philo->eating_mutex)); 
    philo->own_eating_count++;
    pthread_mutex_unlock(&(philo->eating_mutex));
}

void    stop_routine(t_data **data)
{
    int i;

    i = 0;
    while (i < ((*data)->philo_nb))
    {
        if (pthread_join((*data)->philo[i].ph_thread, NULL) != 0)
            return ;
        i++;
    }
    i = 0;
    while (i < (*data)->philo_nb)
    {
        pthread_mutex_destroy(&((*data)->fork[i]));
    }
    pthread_mutex_destroy(&((*data)->printing));
    pthread_mutex_destroy(&((*data)->eating_count_lock));
    pthread_mutex_destroy(&((*data)->death_lock));
    pthread_mutex_destroy(&((*data)->philo->eating_mutex));
}

void    my_wait(t_philo *philo)
{
    printf("id: %d\n", philo->id);
    printf("num: %lld\n", philo->data->philo_nb);
    if (philo->id < philo->data->philo_nb)
    {
        usleep(200);
    }
}

void*   routine(void *philo)
{
    t_philo *temp;
    int i;

    i = 0;
    temp = (t_philo *)philo;
    if ((temp->id % 2) == 0)
    {
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 't');
        usleep(500); 
    }
    while (life_status(&temp) == 0) //this doesnt work properly
    {
        eat_routine(temp);
        if (my_sleep(temp->time_to_sleep, &temp) != 0)
            return (NULL); 
        temp->sleep_start = time_diff(get_time(), temp->data->start_time);
        print_message((temp->data), temp->sleep_start, temp->id, 's');
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 't');
        //printf("eating count: %d %d\n",temp[i].id,  temp[i].own_eating_count);
    }
    return (NULL);
}

void    start_routine(t_data **data)
{
    int i;
    i = 0;
    (*data)->start_time = get_time();
    pthread_mutex_lock(&((*data)->routine_lock));
    while (i < (*data)->philo_nb)
    {
        (*data)->philo[i].id = i + 1;
        if (pthread_create(&((*data)->philo[i].ph_thread), NULL, &routine, &(*data)->philo[i]) != 0) 
        {
            printf("Error with thread creation \n");
            pthread_mutex_unlock(&((*data)->routine_lock));
            return ;
        }
        //printf("eating count: %d %d\n",(*data)->philo[i].id,  (*data)->philo[i].own_eating_count);
        if (life_status(&(*data)->philo) == 1)
            break;
        i++;  
    }
    stop_routine(data);
    pthread_mutex_unlock(&((*data)->routine_lock));
    return ;
}