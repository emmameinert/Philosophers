#include "philo.h"

t_philo *init_philo(char **argv)
{
    t_philo *philo;
    int philosophers;

    philosophers = ft_atol(argv[1]);
    philo = malloc(sizeof(philo) * philosophers);
    if (!philo)
        return (NULL);
    return (philo);
}

t_data *init_data(char **argv)
{
    t_data *data;

    data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
    pthread_mutex_init(&data->left_fork, NULL);
    pthread_mutex_init(&data->right_fork, NULL);
    data->philo = init_philo(argv);
    if (data->philo == NULL)
    {
        printf("Error during allocation\n");
        pthread_mutex_destroy(&data->left_fork);
        pthread_mutex_destroy(&data->right_fork);
        free(data);
        return (0);
    }
	return (data);
}
