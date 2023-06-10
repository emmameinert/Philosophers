#include "philo.h"

t_philo **init_philo(char **argv, t_data *data)
{
    t_philo **philo;
    int philosophers;
    int i;

    i = 0;
    philosophers = ft_atol(argv[1]);
    philo = malloc(sizeof(t_philo) * philosophers); 
    if (!philo)
        return (NULL);
    //data->fork = malloc(sizeof(pthread_mutex_t) * (data->philo_nb)); muss mal spaeter schauen ob das her besser waere als im parsing
    
    while (i < philosophers)
    {
        philo[i] = malloc(sizeof(t_philo) * 1);
        if (!philo[i])
        {
            while (--i > 0)
                free(philo[i]);
        }
        philo[i]->data = data;
        pthread_mutex_init(&((philo[i])->eating_mutex), NULL);
        //pthread_mutex_init(&(philo[i]->data->fork), NULL);
        //pthread_mutex_init(&(data->fork[i]), NULL);
        i++;
    }
    return (philo);
}

t_data *init_data(void)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    return (data);
}

t_data *init_all(void)
{
    t_data *data;
    int i;

    i = 0;
    data = init_data();
    if (data == NULL)   
        return (NULL);
    pthread_mutex_init(&(data->printing), NULL);
    pthread_mutex_init(&(data->eating_count_lock), NULL);
    pthread_mutex_init(&(data->death_lock), NULL);
    pthread_mutex_init(&(data->routine_lock), NULL);
    data->start_time = get_time();
    return (data);
}