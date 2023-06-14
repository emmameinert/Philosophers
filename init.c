#include "philo.h"

t_philo *init_philo(int count)
{
    t_philo *philo;
    int i;

    i = 0;
    philo = malloc(sizeof(*philo) * count); 
    if (!philo)
        return (NULL);
    return (philo);
}


t_data *init_data(char **argv)
{
    t_data *data;

    data = malloc(sizeof((*data)));
    if (!data)
        return (NULL);
    data->philo_nb = ft_atol(argv[1]);
    data->philo = init_philo(data->philo_nb);
    init_mutex(&data);
    return (data);
}

void    init_mutex(t_data **data)
{
    if (pthread_mutex_init(&((*data)->printing), NULL) != 0)
    {
        printf("Error mutex init\n");
    }
    if (pthread_mutex_init(&((*data)->eating_count_lock), NULL) != 0)
    {
        printf("Error mutex init\n");
    }
    if (pthread_mutex_init(&((*data)->death_lock), NULL) != 0)
    {
        printf("Error mutex init\n");
    }
    if (pthread_mutex_init(&((*data)->routine_lock), NULL) != 0)
    {
        printf("Error mutex init\n");
    }
}