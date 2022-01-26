/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:21:41 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/23 21:08:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	check_and_init(int argc, t_all *all, char **argv)
{
	if (check_argument(argc, argv) == -1)
		return (-1);
	if (init_table(argc, all, argv) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	if (check_and_init(argc, &all, argv) == -1)
		return (0);
	while (++i < all.count_philo)
	{
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("Error when forking!\n", 2);
		if (pid == 0)
			life(&all.philo[i]);
		else
			all.pid[i] = pid;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			return (ft_free(&all));
	}
	return (ft_free(&all));
}
