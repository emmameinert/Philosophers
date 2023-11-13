/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:09:55 by emeinert          #+#    #+#             */
/*   Updated: 2023/11/13 12:48:50 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	ms;

	ms = 0;
	if (gettimeofday(&tv, NULL) == 0)
		ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	else
		ms = 0;
	return (ms);
}

long long	time_diff(long long pres, long long past)
{
	long long	diff;

	diff = pres - past;
	return (diff);
}
