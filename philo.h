/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:56:55 by emeinert          #+#    #+#             */
/*   Updated: 2023/06/21 21:38:27 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include    <stdio.h>
# include	<stdlib.h>
# include	<pthread.h>
# include	<unistd.h>
# include	<string.h>
# include	<sys/time.h>

# define NC	"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_mutex_t		eating_count_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		routine_lock;
	pthread_mutex_t		printing;
	unsigned long long	start_time;
	long long			philo_nb;
	pthread_mutex_t		*fork;
	long long			not_each_philo_must_eat;
	int					general_eating_count;
	int					death_flag;
	t_philo				*philo;
}	t_data;

typedef struct s_philo
{
	pthread_t			ph_thread;
	pthread_mutex_t		eating_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			time_to_die;
	unsigned long long	last_meal;
	int					eating_flag;
	t_data				*data;
	int					own_eating_count;
	int					id;
}t_philo;

//input
long long	ft_atol(const char *str);
int			check_input(int argc, char **argv);
int			ft_isdigit(int c);
void		parsing(t_data **data, char **argv);
t_philo		*init_philo(int count);
t_data		*init_data(char **argv);
void		init_forks(t_data **data);

//routine
int			init_mutex(t_data *data);
int			start_routine(t_data **data);
void		*routine(void *philo);
int			eat_routine(t_philo *philo);
int			comp_eat_count(t_philo *philo);
int			death_check(t_philo *philo);
int			life_status(t_philo *philo);
void		monitoring(t_data **data);
void		one_philo(t_philo *philo);

//time
long long	get_time(void);
long long	time_diff(long long pres, long long past);
int			my_sleep(time_t count, t_philo **philo);

//output
int			print_message(t_data *data, time_t time, int id, char message);
void		destroy_mutex(t_data *data);
void		join_mutex(t_data *data);

#endif
