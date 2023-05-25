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

//my own sleeping function
// void    my_sleep()
// {
//     //get time
//     //see how long need to sleep
//     //usleep(500)
//     return ;
// }