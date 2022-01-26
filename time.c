/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:22:22 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/17 16:58:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	now_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000));
}

void	my_usleep(long must_to_be)
{
	long int	first_time;

	first_time = now_time();
	while ((now_time() - first_time) < must_to_be)
		usleep(10);
}

long int	get_time(struct timeval start_time)
{
	struct timeval	tv;
	struct timeval	dif;

	gettimeofday(&tv, NULL);
	dif.tv_sec = tv.tv_sec - start_time.tv_sec;
	dif.tv_usec = tv.tv_usec - start_time.tv_usec;
	return ((dif.tv_sec * 1000) + (dif.tv_usec / 1000));
}
