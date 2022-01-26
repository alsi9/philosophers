/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:22:50 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/23 16:33:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philo)
{
	long int	time_of_death;

	if (get_time(philo->last_eat) > philo->time_to_die)
	{
		sem_wait(philo->sem_print);
		time_of_death = get_time(philo->start_time);
		usleep(50);
		printf("%ld %d died\n", time_of_death, philo->name);
		exit(1);
	}
}

static void	take_fork(t_philo *philo)
{
	check_death(philo);
	sem_wait(philo->sem_fork);
	check_death(philo);
	sem_wait(philo->sem_print);
	printf("%ld %d has taken a fork\n",
		get_time(philo->start_time), philo->name);
	sem_post(philo->sem_print);
	if (philo->count == 1)
		usleep(philo->time_to_die * 1000);
	check_death(philo);
	sem_wait(philo->sem_fork);
	check_death(philo);
	sem_wait(philo->sem_print);
	printf("%ld %d has taken a fork\n",
		get_time(philo->start_time), philo->name);
	sem_post(philo->sem_print);
}

static void	ft_eating(t_philo *philo)
{
	check_death(philo);
	sem_wait(philo->sem_print);
	printf("%ld %d is eating\n", get_time(philo->start_time), philo->name);
	sem_post(philo->sem_print);
	gettimeofday(&philo->last_eat, NULL);
	philo->count_eating++;
}

static void	ft_sleeping_thinking(t_philo *philo)
{
	check_death(philo);
	sem_wait(philo->sem_print);
	printf("%ld %d is sleeping\n",
		get_time(philo->start_time), philo->name);
	sem_post(philo->sem_print);
	my_usleep(philo->time_to_sleep);
	check_death(philo);
	sem_wait(philo->sem_print);
	printf("%ld %d is thinking\n",
		get_time(philo->start_time), philo->name);
	sem_post(philo->sem_print);
	check_death(philo);
}

void	life(t_philo *philo)
{
	if (philo->name % 2 != 0 && philo->count != 1)
		usleep(philo->time_to_eat * 1000);
	while ((philo->count_eating < philo->must_eat) || philo->must_eat == -1)
	{
		take_fork(philo);
		ft_eating(philo);
		my_usleep(philo->time_to_eat);
		sem_post(philo->sem_fork);
		sem_post(philo->sem_fork);
		ft_sleeping_thinking(philo);
		if ((philo->time_to_die < (2 * philo->time_to_eat))
			&& philo->count_eating == 1 && philo->name % 2 == 0)
		{
			my_usleep(philo->time_to_die
				- philo->time_to_eat - philo->time_to_sleep);
			usleep(2000);
			check_death(philo);
		}
	}
	exit(0);
}
