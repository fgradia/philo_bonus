/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:11 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 11:23:57 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long			phils_n;
	long			die_t;
	long			eat_t;
	long			sleep_t;
	long			eat_n;
	long			start;
	pthread_mutex_t	mut_die;
}	t_data;

typedef struct s_philo
{
	pthread_t		*phil;
	long			name;
	long			eat_n;
	long			last_eat;
	long			die;
	long			*f_l_stat;
	pthread_mutex_t	*fork_l;
	long			*f_r_stat;
	pthread_mutex_t	*fork_r;
	t_data			*data;
}	t_philo;

/*		philo.c		****	MAIN	****	*/
long	ft_prec_phil(long actual, long phils_n);
long	ft_next_phil(long actual, long phils_n);
void	ft_init_array(long *array, long val, long phils_n);
void	ft_init_data(char **av, t_data *data);

/*		ft_exit.c	*/
long	ft_thinking(t_philo *actual);
long	ft_sleeping(t_philo *actual);
long	ft_forking(char flag, t_philo	*actual);
long	ft_forking_2(t_philo	*actual);
void	ft_exit(char *str, t_data *data);

/*		ft_start.c	*/
long	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str);
void	ft_start(t_data *data);

/*	utils_basic.c	*/
long	ft_strncmp(char *s1, char *s2, long len);
long	ft_strlen(char *str);
void	ft_write(long fd, char *str);
long	ft_atoi(char *str);
void	ft_write_num(long num);

#endif