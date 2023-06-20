#include "philo.h"

int take_forks(t_philo **philo)
{
    if ((death_check(*philo)) == 0)
    {
        pthread_mutex_lock(((*philo)->left_fork));
        if (print_message(((*philo)->data), time_diff(get_time(), (*philo)->data->start_time), (*philo)->id, 'f') == 1)
        {
            pthread_mutex_unlock(((*philo)->left_fork));
            return (1);
        }
        pthread_mutex_lock(((*philo)->right_fork));
        if (print_message(((*philo)->data), time_diff(get_time(),(*philo)->data->start_time), (*philo)->id, 'f') == 1)
        {
            pthread_mutex_unlock(((*philo)->right_fork));
            pthread_mutex_unlock(((*philo)->left_fork));
            return (1);
        }
        return (0);
    }
    return (1);
}

int    eat_routine(t_philo *philo)
{
    if (philo->data->philo_nb == 1)
    {
        one_philo(philo);
        return (1);
    }
    if (take_forks(&philo))
        return (1);
    pthread_mutex_lock(&(philo->eating_mutex)); 
    philo->own_eating_count++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(philo->eating_mutex));
    if (print_message(philo->data, time_diff(philo->last_meal, philo->data->start_time), philo->id, 'e'))
        return (1);
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

void    one_philo(t_philo *philo)
{
    long long   time;
    pthread_mutex_lock((philo->left_fork));
    print_message((philo->data), time_diff(get_time(), philo->data->start_time), philo->id, 'f');
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

void*   routine(void *philo)
{
    t_philo *temp;

    temp = (t_philo *)philo;
    pthread_mutex_lock(&(temp->data->routine_lock));
    temp->last_meal = temp->data->start_time;
    pthread_mutex_unlock(&(temp->data->routine_lock));
    // pthread_mutex_lock(&(temp->eating_mutex));
    // pthread_mutex_unlock(&(temp->eating_mutex));
    // usleep(100);
    if (temp->data->philo_nb > 1 && ((temp->id % 2) == 0 || temp->id == temp->data->philo_nb))
    {
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 't');
        if (my_sleep(temp->time_to_eat, &temp) == 1)
            return (NULL);
    }
    while(42)
    {
        if(eat_routine(temp) == 1)
            return (NULL);
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 's');
        if (my_sleep(temp->time_to_sleep, &temp) == 1)
            return (NULL);
        print_message((temp->data), time_diff(get_time(), temp->data->start_time), temp->id, 't');
    }
    return (NULL);
}

int    start_routine(t_data **data)
{
    int i;

    i = 0;
    pthread_mutex_lock(&((*data)->routine_lock));
    while (i < (*data)->philo_nb)
    {
        (*data)->philo[i].id = i + 1;
        if (pthread_create(&((*data)->philo[i].ph_thread), NULL, &routine, &(*data)->philo[i]) != 0)
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
 