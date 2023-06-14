#include "philo.h"

void    init_forks(t_data **data)
{
    int i;
    
    i = 0;
    (*data)->fork = malloc(sizeof(pthread_mutex_t) * ((*data)->philo_nb));
    if (!(*data)->fork)
        return ;
    while (i < (*data)->philo_nb)
    {
        pthread_mutex_init(&((*data)->fork[i]), NULL);
        i++;
    }
    i = 0;
    while (i < (*data)->philo_nb)
    {
        if (i == (*data)->philo_nb - 1)
        {
            (*data)->philo[i].left_fork = &(*data)->fork[i];
            (*data)->philo[i].right_fork = (*data)->philo[0].left_fork; //passt das so?
        }
        else
        {
            (*data)->philo[i].left_fork = &(*data)->fork[i];
            (*data)->philo[i].right_fork = &(*data)->fork[i + 1];
        }
        i++;
    }
}

void    parsing(t_data **data, char **argv)
{
    int i;

    i = 0;
    (*data)->general_eating_count = 0;
    while (i < (*data)->philo_nb)
    {
        (*data)->philo[i].data = (*data);
        (*data)->philo[i].time_to_die = ft_atol(argv[2]);
        (*data)->philo[i].time_to_eat = ft_atol(argv[3]);
        (*data)->philo[i].time_to_sleep = ft_atol(argv[4]);
        (*data)->philo[i].own_eating_count = 0;
        (*data)->philo[i].last_meal = 0;
        (*data)->philo[i].old_time = (*data)->start_time;
        pthread_mutex_init(&((*data)->philo[i].eating_mutex), NULL);
        i++;
    }
    if(argv[5])
    {
        (*data)->not_each_philo_must_eat = ft_atol(argv[5]);
    }
    else
        (*data)->not_each_philo_must_eat = -1;
    init_forks(data);
}
