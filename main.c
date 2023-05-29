#include "philo.h"

void   start_routine(char **argv, t_data *data)
{
    int i;
    i = 0;

    if (!parse_input(argv, data)) //check this before init data 
        return ;
    pthread_mutex_lock(&data->mutex);
    while (i < data->philosopher)
    {
        printf("hello\n");
        // data->philo[i].th = malloc(sizeof(data->philosopher));
        data->philo->id = i;
        if (pthread_create(&data->philo[i].th, NULL, &routine, NULL) != 0) //maybe double pointer for data
        {
            printf("error with thread creation \n");
            return ;
            //need to differ between even and odd philosopher for the eating and thinking
        
        }
        //joooooin
        printf("i: %d\n", i);
        i++;
    }
    pthread_mutex_unlock(&data->mutex);
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
