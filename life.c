/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:22:50 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/21 19:04:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo)
{
	if ((*philo->died_threads) != philo->count)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print);
		printf("%ld %d has taken a fork\n",
			get_time(philo->start_time), philo->name);
		pthread_mutex_unlock(philo->print);
	}
	if ((*philo->died_threads) != philo->count)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print);
		printf("%ld %d has taken a fork\n",
			get_time(philo->start_time), philo->name);
		pthread_mutex_unlock(philo->print);
	}
}

static void	ft_eating(t_philo *philo)
{
	if ((*philo->died_threads) != philo->count)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld %d is eating\n", get_time(philo->start_time), philo->name);
		pthread_mutex_unlock(philo->print);
		gettimeofday(&philo->last_eat, NULL);
		philo->count_eating++;
	}
	my_usleep(philo->time_to_eat);
}

static void	ft_sleeping_thinking(t_philo *philo)
{
	if ((*philo->died_threads) != philo->count)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld %d is sleeping\n",
			get_time(philo->start_time), philo->name);
		pthread_mutex_unlock(philo->print);
	}
	my_usleep(philo->time_to_sleep);
	if ((*philo->died_threads) != philo->count)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld %d is thinking\n",
			get_time(philo->start_time), philo->name);
		pthread_mutex_unlock(philo->print);
	}
}

void	*life(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->name % 2 != 0 && philo->count != 1)
		usleep(philo->time_to_eat * 1000);
	while ((philo->count_eating < philo->must_eat) || philo->must_eat == -1)
	{
		take_fork(philo);
		ft_eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_sleeping_thinking(philo);
	}
	(*philo->died_threads)++;
	philo->poel_vse_stop_proverka = 1;
	return (NULL);
}
