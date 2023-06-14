#include "philo.h"

unsigned long long get_time()
{
    struct timeval tv;
    unsigned long long ms;

    ms = 0;
    if (gettimeofday(&tv, NULL) == 0)
        ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    else 
        ms = 0;
    return (ms);
}

long long   time_diff(unsigned long long pres, unsigned long long past)
{
    long long diff;

    diff = pres - past;
    return (diff);
}