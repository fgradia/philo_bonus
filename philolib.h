/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:11 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 09:56:33 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

//	memset, prlongf, malloc, free, write,
//	usleep, gettimeofday,	
//	pthread_create,
//	pthread_detach, 
//	pthread_join, 
//	pthread_join() is a blocking call, 
//		it will block the calling thread until the other thread ends.
//		First parameter of pthread_join() is the ID of target thread.
//	pthread_mutex_init,
//	pthread_mutex_destroy, 
//	pthread_mutex_lock,
//	pthread_mutex_unlock

//	number_of_philosophers
//	time_to_die 
//	time_to_eat
//	time_to_sleep 
//	number_of_times_each_philosopher_must_eat]

typedef struct s_data
{
	long		phils_n;
	long		die_t;
	long		eat_t;
	long		sleep_t;
	long		eat_n;
	long		start;
	// t_philo	**phils;

	// long				x;
	// long				*fork;
	// long				*fork;			//	0 == disponibile ; 1 == eating ; 2 == blocked 
	// long				*die;			//	pari == eating ; dispari == inattivo 
	// pthread_t		*phil;
	// pthread_t		*dying_phil;
	pthread_mutex_t	mut_die;
	// pthread_mutex_t	*mut_fork;
	
}	t_data;

typedef struct s_philo
{
	pthread_t		*phil;
	long				name;
	long				eat_n;
	long				last_eat;
	long				die;
	long				*f_l_stat;
	pthread_mutex_t	*fork_l;
	long				*f_r_stat;
	pthread_mutex_t	*fork_r;
	t_data			*data;
}	t_philo;


// t_data	data;

/*		philo.c		****	MAIN	****	*/
long		ft_prec_phil(long actual, long phils_n);
long		ft_next_phil(long actual, long phils_n);
void	ft_init_array(long *array, long val, long phils_n);
// void	ft_init_array(long *array, long val);
void	ft_init_data(char **av, t_data *data);

/*		ft_exit.c	*/
void	ft_exit(char *str, t_data *data);

/*		ft_start.c	*/
void	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str);
void	ft_start(t_data *data);

/*	utils_basic.c	*/
long		ft_strncmp(char *s1, char *s2, long len);
long		ft_strlen(char *str);
void	ft_write(long fd, char *str);
long		ft_atoi(char *str);
char	*ft_itoa(long num);
void	ft_write_num(long num);

#endif