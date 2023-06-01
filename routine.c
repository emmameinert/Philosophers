#include "philo.h"

void*    routine(void *philo)
{
    t_philo *temp;

    temp = (t_philo *)philo;
    pthread_mutex_lock(&(temp->data->left_fork));
    printf("hello\n");
    pthread_mutex_unlock(&(temp->data->left_fork));
    pthread_mutex_lock(&(temp->data->right_fork));
    printf("%d\n", temp->id);
    pthread_mutex_unlock(&(temp->data->right_fork));
    return (NULL);
}

void    start_routine(t_philo **philo)
{
    int i;

    i = 0;
    printf("%lld\n", (philo[7])->data->philo_nb);
    pthread_mutex_lock(&((*philo)->data->eating_lock)); //error
    while (i < (*philo)->data->philo_nb)
    {
        philo[i]->id = i + 1;
        printf("%d\n", philo[i]->id);
        if (pthread_create(&(philo[i]->ph_thread), NULL, &routine, philo[i]) != 0) 
        {
            printf("Error with thread creation \n");
            return ;
        }
        i++;   
    }
    printf("hierr: %d\n", i);
    i = 0;
    while (i < (*philo)->data->philo_nb)
    {
        if (pthread_join(philo[i]->ph_thread, NULL) != 0)
        {
            printf("mannn\n");
            return ;
        }
        i++;
    }
    pthread_mutex_unlock(&((*philo)->data->eating_lock));
}