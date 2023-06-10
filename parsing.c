#include "philo.h"

void    parsing(t_data *data, char **argv, t_philo **philo)
{
    int i;
    
    i = 0;
    data->philo_nb = ft_atol(argv[1]);
    data->fork = malloc(sizeof(pthread_mutex_t) * (data->philo_nb));
    if (!data->fork)
        return ;
    while (i < data->philo_nb)
    {
        philo[i]->time_to_die = ft_atol(argv[2]);
        philo[i]->time_to_eat = ft_atol(argv[3]);
        philo[i]->time_to_sleep = ft_atol(argv[4]);
        pthread_mutex_init(&(data->fork[i]), NULL);
        i++;
    }
    i = 0;
    while (i < data->philo_nb)
    {
        if (i == data->philo_nb - 1)
        {
            philo[i]->left_fork = &data->fork[i];
            philo[i]->right_fork = philo[0]->left_fork; //passt das so?
        }
        else
        {
            philo[i]->left_fork = &data->fork[i];
            philo[i]->right_fork = &data->fork[i + 1];
        }
        i++;
    }
    if(argv[5])
    {
        data->not_each_philo_must_eat = ft_atol(argv[5]);
    }
    else
        data->not_each_philo_must_eat = -1;
}
