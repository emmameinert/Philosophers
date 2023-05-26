#include "philo.h"

void*  routine(void *philo)
{
    int eaten;
    t_philo *temp;
    //long long time; 

    temp = (t_philo *)philo;
    eaten = 0;
    temp[temp->id].start_time = get_time();
    printf("flag: %d\n", temp->simu_flag); //finally works
    printf("time : %lld\n", temp[temp->id].start_time);
    // if (temp->simu_flag == 1)
    // {
    //     while (eaten < temp->data->not_each_philo_must_eat)
    //     {
    //         if ((temp->id % 2) == 0)
    //         {
    //             time  = time_diff(philo);//wait and think first
    //             printf("[%lld] %s Philosopher starts thinking\n",time, GREEN);
    //         }
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
    return (philo);
}  

