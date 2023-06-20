#include "philo.h"

void monitoring(t_data **data)
{
    int i;
    int flag;

    flag = 0;
    while (flag == 0)
    {
        i = 0;
        while (i < (*data)->philo_nb)
        {
			if ((*data)->philo_nb < 150)
            	usleep(1200);
			else
            	usleep(35000);
            if (life_status(&((*data)->philo[i])) > 0)
                i++;
            if (time_diff(get_time(), (*data)->start_time) >= (*data)->philo->time_to_die)
            {
                if (death_check(&(*data)->philo[i]) || life_status(&((*data)->philo[i])) > 0)
                    i++;
            }
            if (i == (*data)->philo_nb)
                flag = 1;
		}
    }
}

int main(int argc, char **argv)
{
    t_data *data;

    data = NULL;
    if (argc != 5 && argc != 6)
    {
        printf("Error with number of arguments\n");
        return (0);
    }
    if (check_input(argc, argv) == 1)
        return (0);
    data = init_data(argv);
    if (data == NULL)
        return (0);
    parsing(&data, argv);
    start_routine(&data);
    monitoring(&data);
    destroy_mutex(data);
    free(data->fork);
    free(data->philo);
    free(data);
    return (0);
}
