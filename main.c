#include "philo.h"

int main(int argc, char **argv)
{
    t_data *data;

    data = NULL;
    if (argc != 5 && argc != 6)
    {
        printf("Error with number of arguments\n"); // Maybe it's a good idea to print this message in stderr (STDERR_FILENO)
        return (0);
    }
    if (check_input(argc, argv) == 1)
        return (0);
    data = init_data(argv);
    if (data == NULL)
        return (0);
    parsing(&data, argv);
    start_routine(&data);
    pthread_mutex_destroy(&(data)->routine_lock);
    // //need to free the forks probably
    free(data->philo);
    free(data);
    return (0);
}