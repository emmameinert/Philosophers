
#ifndef PHILO_H
#   define PHILO_H

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

typedef struct s_data t_data;

typedef struct s_philo t_philo;

typedef struct s_data
{
    int     philosopher;
    int     forks[2];
    int     not_each_philo_must_eat;
    int     eating_count;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    pthread_mutex_t mutex;
    t_philo *philo;
}t_data;

typedef struct s_philo
{
    int     simu_flag;
    long long start_time;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    int id;
    pthread_t *th;
    t_data *data;
}t_philo;

//input
int check_input(int argc, char **argv);
t_data *init_data(char **argv);
t_philo *init_philo(char **argv);
int    parse_input(char **argv, t_data *data);
int	ft_isdigit(int c);

//time
long long   get_time();
long long   time_diff(t_philo *philo);

//routines
void   start_routine(char **argv, t_data *data);
void*  routine(void *data);

//utils

long long	ft_atol(const char *str);
void        my_sleep();

#endif