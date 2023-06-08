#ifndef PHILO_H
    #define PHILO_H

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
    pthread_mutex_t eating_lock;
    pthread_mutex_t eating_count_lock;
    pthread_mutex_t death_lock;
    pthread_t    monitoring;
    pthread_mutex_t printing;
    time_t  start_time;
    long long     philo_nb;
    pthread_mutex_t fork[philo_nb];
    long  long    not_each_philo_must_eat;
    long long     simu_flag;
    int           eating_count;
}t_data;

typedef struct s_philo
{
    pthread_t ph_thread;
    pthread_mutex_t eating_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    time_t  time_to_eat;
    time_t  time_to_sleep;
    time_t  time_to_die;
    time_t  last_meal;
    time_t  sleep_start;
    t_data *data;
    int id;
}t_philo;

//input
long long	ft_atol(const char *str);
int         check_input(int argc, char **argv);
int	        ft_isdigit(int c);
void        parsing(t_data *data, char **argv, t_philo **philo);
t_philo     **init_philo(char **argv, t_data *data);
t_data      *init_data(void);
//routine

t_data  *init_all(void);
void    start_routine(t_philo **philo);
void*   routine(void *philo);
void    eat_routine(t_philo *philo);
int     comp_eat_count(t_philo *philo);
void    stop_routine(t_philo **philo);
int     death_check(t_philo **philo);
//time

long long   get_time();
long long   time_diff(long long pres, long long past);
void        my_sleep(t_philo *philo);

//output
void    print_message(t_data *data, time_t time, int id, char message);
void    free_struct(t_philo **philo, long philo_nb);

#endif