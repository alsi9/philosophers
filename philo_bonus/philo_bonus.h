/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:58:19 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/17 15:44:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <sys/fcntl.h>
# include <sys/semaphore.h>

typedef struct s_philo
{
	int				time_to_die;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	int				count;
	int				must_eat;
	int				count_eating;
	int				time_to_eat;
	int				time_to_sleep;
	int				name;
	struct timeval	last_eat;
	struct timeval	start_time;
}	t_philo;

typedef struct s_all
{
	t_philo			*philo;
	pid_t			*pid;
	int				count_philo;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	struct timeval	start_time;
}	t_all;

void		ft_putstr_fd(char *s, int fd);
int			ft_free(t_all *all);
int			check_argument(int argc, char **argv);
void		life(t_philo *philo);
int			ft_atoi(char *str, int i, int m);
void		my_usleep(long must_to_be);
long int	get_time(struct timeval start_time);
int			init_all(t_all *all, char **argv);
int			init_philo(int argc, t_all *all, char **argv, int i);
int			init_table(int argc, t_all *all, char **argv);

#endif
