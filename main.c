#include "philo.h"

int main(int argc, char **argv)
{
    t_philo **philo;
    t_data *data;

    if (argc != 5 && argc != 6)
    {
        printf("Error with number of arguments\n");
        return (0);
    }
    if (check_input(argc, argv) == 1)
        return (0);
    data = init_all();
    philo = init_philo(argv, data);
    if ((*philo) == NULL)
        return (0);
    parsing((*philo)->data, argv, philo);
    //printf("%lld\n",(*philo)->data->philo_nb);
    start_routine(philo);
    pthread_mutex_destroy(&(*philo)->data->eating_lock);
    pthread_mutex_destroy(&(*philo)->data->left_fork);
    pthread_mutex_destroy(&(*philo)->data->right_fork);
    free((*philo)->data);
    return (0);
}
