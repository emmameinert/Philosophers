#include "philo.h"

int	ft_isdigit(int c)
{
	int	answer;

	answer = 0;
	if (c >= 48 && c <= 57)
		answer = 1;
	else
		answer = 0;
	return (answer);
}

static int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int ft_is_negative(char c)
{
    if (c == '-')
        return (1);
    else
        return(0);
}

int    check_input(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < (argc))
    {
		if (ft_is_negative(argv[i][0]) || ft_is_number(argv[i]))
        	return (1);
		i++;
	}
    return (0);
}

int    parse_input(char **argv, t_data *data)
{
    data->philosopher = ft_atol(argv[1]);
	if (data->philosopher > 200 || data->philosopher == 0)
	{
		printf("Error: wrong amount of Philosophers\n");
		return (0);
	}
    data->philo->time_to_die = ft_atol(argv[2]);
    data->philo->time_to_eat = ft_atol(argv[3]);
    data->philo->time_to_sleep = ft_atol(argv[4]);
	if ((data->philo->time_to_die < 60) || (data->philo->time_to_eat < 60) 
		|| (data->philo->time_to_sleep < 60))
	{
		printf("Error: too little time\n");
		return (0);
	}
    if (argv[5])
    {
		data->not_each_philo_must_eat = ft_atol(argv[5]);
		if (data->not_each_philo_must_eat == 0)
		{
			printf("Eating count is 0: Philosophers don't have to eat\n");
			return (0);
		}
	}
    return (1);
}
