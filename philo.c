#include "philo.h"

pthread_mutex_t mutex;
int* eaten;

int	ft_atoi(const char *str)
{
	long	i;
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (sign * result > 2147483647)
			return (-1);
		if (sign * result < -2147483648)
			return (0);
	}
	return ((int)sign * (int)result);
}

void*  routine()
{
    int i;
    i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        eaten++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return (eaten);
}  

int main(int argc, char **argv)
{
    int philosophers;
    int i;
    long timestamp;
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    eaten = 0;
    i = 1;
    if (argc != 2)
        return (0);
    philosophers = ft_atoi(&argv[1][0]);
    pthread_t th[philosophers];
    pthread_mutex_init(&mutex, NULL);
    while (i <= philosophers)
    {
        if (pthread_create(th + i , NULL, &routine, NULL) != 0)
        {
            printf("error with thread creation \n");
            return 1;
        }
        if (i == 1)
        {
            philo->start_time = convert_time();
            //printf("2. : %ld\n", philo->start_time);
        }
        timestamp = time_diff(philo);
        printf("timestamp[%ld ms]: Thread has started\n", timestamp);
        if (pthread_join(th[i], NULL) != 0)
            return 2;
        timestamp = time_diff(philo);
        printf("timestamp[%ld ms]: Thread %d has finished\n",timestamp, i);
        i++;
    }
    pthread_mutex_destroy(&mutex);
    free(philo);
    return (0);
}
