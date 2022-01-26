/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:22:09 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/22 20:48:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_all(t_all *all, char **argv)
{
	all->count_philo = ft_atoi(argv[1], 0, 1);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->count_philo);
	if (!(all->philo))
		return (-1);
	all->pid = (pid_t *)malloc(sizeof(pid_t) * all->count_philo);
	if (!(all->pid))
	{
		free(all->philo);
		return (-1);
	}
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	all->sem_fork = sem_open("sem_fork", O_CREAT, 0644, all->count_philo);
	all->sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	return (0);
}

int	init_philo(int argc, t_all *all, char **argv, int i)
{
	while (++i < all->count_philo)
	{
		all->philo[i].count = all->count_philo;
		all->philo[i].sem_fork = all->sem_fork;
		all->philo[i].sem_print = all->sem_print;
		all->philo[i].last_eat = all->start_time;
		all->philo[i].start_time = all->start_time;
		all->philo[i].count_eating = 0;
		all->philo[i].time_to_die = ft_atoi(argv[2], 0, 1);
		all->philo[i].time_to_eat = ft_atoi(argv[3], 0, 1);
		all->philo[i].time_to_sleep = ft_atoi(argv[4], 0, 1);
		if (argc == 6)
			all->philo[i].must_eat = ft_atoi(argv[5], 0, 1);
		else
			all->philo[i].must_eat = -1;
		all->philo[i].name = i + 1;
	}
	return (0);
}

int	init_table(int argc, t_all *all, char **argv)
{
	gettimeofday(&all->start_time, NULL);
	if (init_all(all, argv) == -1)
		return (-1);
	init_philo(argc, all, argv, -1);
	return (0);
}
