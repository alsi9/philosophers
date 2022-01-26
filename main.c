/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:21:41 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/21 19:03:15 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_palach(t_philo *philo, t_all *all)
{
	long int	time_of_death;
	int			i;

	i = 0;
	*philo->died_threads = all->count_philo;
	pthread_mutex_lock(philo->print);
	time_of_death = get_time(philo->start_time);
	printf("%ld %d died\n", time_of_death, philo->name);
	while (i < all->count_philo)
	{
		pthread_detach(all->threads[i]);
		i++;
	}
}

void	*ft_slezhka_smerti(t_all *all)
{
	int	i;

	i = 0;
	usleep(all->philo[0].time_to_die * 1000);
	while (all->died_threads != all->count_philo)
	{
		if (all->philo[i].time_to_die < get_time(all->philo[i].last_eat)
			&& all->philo[i].poel_vse_stop_proverka == 0)
		{
			ft_palach(&all->philo[i], all);
			break ;
		}
		i++;
		if (i == all->count_philo)
			i = 0;
	}
	return (NULL);
}

int	check_argument(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("wrong count of arguments!\n", 2);
		return (-1);
	}
	while (++i < argc)
	{
		if (ft_atoi(argv[i], 0, 1) <= 0)
		{
			ft_putstr_fd("incorrect argument!\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (check_argument(argc, argv) == -1)
		return (0);
	if (init_table(argc, &all, argv) == -1)
		return (0);
	ft_slezhka_smerti(&all);
	ft_free(&all);
	return (0);
}
