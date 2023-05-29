#include "philo.h"

void*  routine(void *philo)
{
    int eaten;
    //t_philo *temp;
    //long long time; 
    //temp = (t_philo *)philo;
    printf("ROUTINE\n");
    // printf("thread %d\n", temp->id);
    // pthread_mutex_lock(&temp->data->left_fork);
    // pthread_mutex_unlock(&temp->data->left_fork);
    eaten = 0;
    // pthread_mutex_lock(&temp->data->mutex);
    // pthread_mutex_unlock(&temp->data->mutex);
    //         if ((temp->id % 2) == 0)
    //         {
    //             time  = time_diff(philo);//wait and think first
    //             printf("[%lld] %s Philosopher starts thinking\n",time, GREEN);
    //         }
                //else
                //eat
    
    // temp[temp->id].start_time = get_time();
    // //printf("flag: %d\n", temp->simu_flag); //finally works
    // printf("time : %lld\n", temp[temp->id].start_time);
    // if (temp->simu_flag == 1)
    // {
    //     while (eaten < temp->data->not_each_philo_must_eat)
    //     {
    //     eaten++;
        //grab forks
        //eating
        //wating
        //pthread_mutex_lock(&left_fork);
        //pthread_mutex_lock(&rigth_fork);
        //time_diff(temp->philo);
        //eaten++;
        //pthread_mutex_unlock(&left_fork);
        //pthread_mutex_unlock(&rigth_fork);
        //sleeping
        
    //     }
    // }
    //join every thread 
    return (philo);
}  

