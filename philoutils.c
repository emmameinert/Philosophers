#include "philo.h"

void    my_sleep(t_philo *philo)
{
    while (!dead)
    {
        ms = get_time()
        if (time_diff(i, timestemp >= time))
            break ;
        usleep (150);
    }
}
void*   routine(void *philo)
{
    if (philo->id % 2 == 0)
     usleep(15000);
    while (!died)
    {
        eat_routine(philo);
        if (all->eaten)
            break;
        print('s');
        my_sleep();
        print('t');
        i++;
    }
    return (NULL);
}

void    eat_routine(t_philo *philo)
{
    lock;
    print('f');
    lock; 
    print('f');
    lock eat;
    print('e');
    unlock eat;
    my_sleep();
    eat_count++;
    unlock;
    unlock; 
}

