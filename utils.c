#include "philo.h"

static long long	ft_check_char(const char *str, int i, long sign, long result)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			result = 0;
		result = result * 10 + (str[i] - '0');
		i++;
		if (sign * result > 2147483647)
			return (2147483648);
		if (sign * result < -2147483648)
			return (-21474836489);
	}
	return (sign * result);
}

long long	ft_atol(const char *str)
{
	long	i;
	long	result;
	long	sign;

	result = 2147483648;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (!ft_isdigit(str[i]))
			return (result);
	}
	result = ft_check_char(str, i, sign, result);
	return (result);
}

void    my_sleep(t_philo *philo)
{
    long long time;
	time = get_time();
	// while (//death_check)
	// {
		if (time_diff(time, get_time()) >= philo->time_to_sleep)
			break ;
		usleep(50);
	// }
    return ;
}