/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:11 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/13 17:58:55 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/fcntl.h>

typedef struct s_data
{
	long			phils_n;
	long			die_t;
	long			eat_t;
	long			sleep_t;
	long			eat_n;
	long			start;
	long			die_all;
	void			*tofree;
}	t_data;

typedef struct s_philo
{
	sem_t			*die_sem;
	sem_t			*semaphore;
	int				phid;
	long			name;
	long			eat_n;
	long			last_eat;
	long			last_sleep;
	t_data			*data;
}	t_philo;

/*		philo.c		****	MAIN	****	*/
long	ft_next_phil(long actual, long phils_n);
void	ft_init_array(long *array, long val, long phils_n);
void	ft_init_data(char **av, t_data *data);

/*		ft_exit.c	*/
int		ft_find_phid(t_philo *philos, int x);
void	ft_check_eat(t_philo *philos, t_data *data, int first, int *ret);
long	ft_thinking222(t_philo *actual, sem_t *semaphore);
void	ft_kill(t_philo *philos, int x, t_data *data);
void	ft_exit(char *str, t_data *data);

/*		ft_start.c	*/
void	ft_eat_sleep_think(t_philo *actual, sem_t *semaphore);
void	ft_routine(t_philo	*philos, int actual);
void	ft_check_piddio(t_philo *philos, t_data *data);
void	ft_create_philo(t_philo *philos, t_data *data, int x);
void	ft_start(t_data *data);

/*	utils_basic.c	*/
long	ft_strncmp(char *s1, char *s2, long len);
void	ft_write(long fd, char *str);
long	ft_atoi(char *str);
void	ft_write_num(long num);

/*	utils_start.c	*/
void	ft_alone(t_philo *actual);
int		ft_dead(long x, t_philo *actual, t_data *data);
long	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str);
void	ft_flag_usleep(int flag, long *x, t_philo *actual);
long	ft_usleep(int flag, t_philo *actual, t_data *data);

#endif