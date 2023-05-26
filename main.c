#include "philo.h"

// void*  routine(void *philo)
// {
//     t_philo *temp;

//     temp = (t_philo *)philo;
//     int i;
//     i = 0;
//     while (i < 10000000) //??
//     {
//         // pthread_mutex_lock(&mutex);
//         // //eaten++;
//         // pthread_mutex_unlock(&mutex);
//         i++;
//     }
//     return (eaten);
// } 

void   start_routine(char **argv, t_data *data)
{
    int i;
    i = 0;

    if (!parse_input(argv, data))
        return ;
    while (i < data->philosopher)
    {
        data->philo[i].th = malloc(sizeof(data->philosopher));
        data->philo->id = i;
        pthread_mutex_init(&data->mutex, NULL);
        if (pthread_create(data->philo[i].th, NULL, &routine, data->philo) != 0) 
        {
            printf("error with thread creation \n");
            return ;
            //need to differ between even and odd philosopher for the eating and thinking
        }
        i++;
    }
    pthread_mutex_destroy(&data->mutex);

}


int main(int argc, char **argv)
{
    t_data *data;

    if (argc != 5 && argc != 6)
    {
        printf("Error with number of arguments\n");
        return (0);
    }
    if (check_input(argc, argv) == 1)
    {
        printf("Error: Wrong arguments\n");
        return (0);
    }
    data = init_data(argv);
    if (data == NULL)
    {
        printf("Error during allocation\n");
        return (0);
    }
    start_routine(argv, data);
    // while (1)
    // let monitoring script run the whole time of the program and compare and see if someone died  //pthread_mutex_destroy(&mutex);
    free(data->philo);
    free(data);
    return (0);
}
