#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

typedef	struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}	t_locks;

typedef struct s_philo
{
    long start_time;
}t_philo;

//time
long    convert_time();
long    time_diff(t_philo *philo);

#endif