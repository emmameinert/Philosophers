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
    //long timestamp;
    i = 1;

    if (!parse_input(argv, data))
        return ;
    // pthread_t th[data->philosopher];
    // while (i <= data->philosopher)
    // {
    //     if (pthread_create(th + i , NULL, &routine, NULL) != 0)
    //     {
    //         printf("error with thread creation \n");
    //         return 1;
    //     }
    //     if (i == 1)
    //     {
    //         data->philo->start_time = get_time();
    //         printf("2. : %ld\n", data->philo->start_time);
    //     }
    //     i++;
    // }

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
    data = init_data();
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
    printf("%s HELLO\n", RED);
    return (0);
}
