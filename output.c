#include "philo.h"

void    print_message(t_data *data, time_t time, int id, char message)
{
    pthread_mutex_lock(&data->printing);
    //double check everytime if somebody has died
    if (message == 'f')
    {
        printf("%s%ld %d %s",YELLOW, time, id, "has taken a fork\n");
    }
    else if (message == 'e')
    {
        printf("%s%ld %d %s", BYELLOW, time, id, "is eating\n");
    }
    else if (message == 's')
    {
        printf("%s%ld %d %s", NC, time, id, "is sleeping\n");
    }
    else if (message == 't')
    {
        printf("%s%ld %d %s", GREEN, time, id, "is thinking\n");
    }
    else if (message == 'd')
    {
        printf("%s%ld %d %s", RED, time, id, "died\n");
    }
    pthread_mutex_unlock(&data->printing);
    return ;
}