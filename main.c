#include "philo.h"

int death_check(t_philo **philo)
{
    int i;

    i = 0;
    while (i < (*philo)->data->philo_nb)
    {
        pthread_mutex_lock(&((*philo)->data->death_lock));
        if ((philo[i]->last_meal > 0) && (time_diff(philo[i]->last_meal) > philo[i]->time_to_die)) //vor dem ersten meal logischerweise falsche zeit, weil es noch kein meal gab. somti loest da aus und die philos sterben sofort
        {
            print_message(((*philo)->data), time_diff((*philo)->data->start_time), (philo[i])->id, 'd');
            pthread_mutex_unlock(&((*philo)->data->death_lock));
            return (1);
        }
        pthread_mutex_unlock(&((*philo)->data->death_lock));
        i++; 
    //maybe add the eating count here
    }
    return (0);
}

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
    start_routine(philo);
    pthread_mutex_destroy(&(*philo)->data->eating_lock);
    free((*philo)->data); //ist das richtig so?
    free_struct(philo, (*philo)->data->philo_nb);
    return (0);
}
