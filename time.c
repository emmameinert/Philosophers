#include "philo.h"

long convert_time()
{
    long ms;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    //printf("1. : %ld\n", ms);
    return (ms);
}

long    time_diff(t_philo *philo)
{
    long ms;
    long diff;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    diff = ms - philo->start_time;
    return (diff);
}