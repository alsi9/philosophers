/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:22:09 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/21 19:15:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_all *all, char **argv)
{
	all->count_philo = ft_atoi(argv[1], 0, 1);
	all->died_threads = 0;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->count_philo);
	if (!(all->philo))
		return (-1);
	return (0);
}

void	init_philo(int argc, t_all *all, char **argv, int i)
{
	while (++i < all->count_philo)
	{
		all->philo[i].count = all->count_philo;
		all->philo[i].print = all->print;
		all->philo[i].poel_vse_stop_proverka = 0;
		all->philo[i].died_threads = &all->died_threads;
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
		all->philo[i].left_fork = &all->forks[i];
		if (i == (all->count_philo - 1))
			all->philo[i].right_fork = &all->forks[0];
		else
			all->philo[i].right_fork = &all->forks[i + 1];
	}
}

int	init_thread(t_all *all)
{
	int	i;

	i = 0;
	all->threads = (pthread_t *)malloc(sizeof(pthread_t) * all->count_philo);
	if (!(all->threads))
		return (-1);
	while (i < all->count_philo)
	{
		if (pthread_create(&all->threads[i], NULL, life, &all->philo[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_forks(t_all *all)
{
	int	i;

	i = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * (all->count_philo));
	if (!(all->forks))
	{
		free(all->philo);
		return (-1);
	}
	while (++i < all->count_philo)
		pthread_mutex_init(&all->forks[i], NULL);
	all->print = malloc(sizeof(pthread_mutex_t));
	if (!(all->print))
	{
		free(all->philo);
		free(all->forks);
		return (-1);
	}
	pthread_mutex_init(all->print, NULL);
	return (0);
}

int	init_table(int argc, t_all *all, char **argv)
{
	gettimeofday(&all->start_time, NULL);
	if (init_all(all, argv) == -1)
		return (-1);
	if ((init_forks(all)) == -1)
		return (-1);
	init_philo(argc, all, argv, -1);
	if (init_thread(all) == -1)
	{
		free(all->philo);
		free(all->forks);
		free(all->print);
		return (-1);
	}
	return (0);
}
