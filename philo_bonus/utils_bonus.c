/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:21:56 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/22 21:06:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_free(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->count_philo)
		kill(all->pid[i], SIGKILL);
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	free(all->philo);
	free(all->pid);
	sem_close(all->sem_fork);
	sem_close(all->sem_print);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("		THE END\n", 1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

int	ft_atoi(char *str, int i, int m)
{
	long int	n;

	n = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + m * (str[i] - 48);
		i++;
		if (m == 1 && n < 0 && i > 18)
			return (-1);
		else if (m == -1 && n > 0 && i > 19)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	return (n);
}
