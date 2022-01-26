/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:58:19 by ephantom          #+#    #+#             */
/*   Updated: 2022/01/21 19:10:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	int				time_to_die;
	int				*died_threads;
	int				count;
	int				must_eat;
	int				count_eating;
	int				time_to_eat;
	int				time_to_sleep;
	int				name;
	int				poel_vse_stop_proverka;
	struct timeval	last_eat;
	struct timeval	start_time;
}	t_philo;

typedef struct s_all
{
	t_philo			*philo;
	int				count_philo;
	int				died_threads;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	struct timeval	start_time;
}	t_all;

void		ft_putstr_fd(char *s, int fd);
void		ft_free(t_all *all);
int			check_argument(int argc, char **argv);
void		*life(void *phil);
int			ft_atoi(char *str, int i, int m);
void		my_usleep(long must_to_be);
long int	get_time(struct timeval start_time);
int			init_all(t_all *all, char **argv);
void		init_philo(int argc, t_all *all, char **argv, int i);
int			init_thread(t_all *all);
int			init_forks(t_all *all);
int			init_table(int argc, t_all *all, char **argv);

#endif
