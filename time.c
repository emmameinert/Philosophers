#include "philo.h"

long long get_time()
{
    long ms;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    return (ms);
}

long long   time_diff(long long pres, long long past)
{
    long long diff;

    diff = pres - past;
    return (diff);
}
