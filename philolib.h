/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:11 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/17 14:35:08 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

//	memset, printf, malloc, free, write,
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
	int		phils_n;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		eat_n;
	int		start;
	// t_philo	**phils;

	// int				x;
	// int				*fork;
	// int				*fork;			//	0 == disponibile ; 1 == eating ; 2 == blocked 
	// int				*die;			//	pari == eating ; dispari == inattivo 
	// pthread_t		*phil;
	// pthread_t		*dying_phil;
	pthread_mutex_t	mut_die;
	// pthread_mutex_t	*mut_fork;
	
}	t_data;

typedef struct s_philo
{
	pthread_t		*phil;
	int				name;
	int				eat_n;
	int				last_eat;
	int				die;
	int				*f_l_stat;
	pthread_mutex_t	*fork_l;
	int				*f_r_stat;
	pthread_mutex_t	*fork_r;
	t_data			*data;
}	t_philo;


// t_data	data;

/*		philo.c		****	MAIN	****	*/
int		ft_prec_phil(int actual, int phils_n);
int		ft_next_phil(int actual, int phils_n);
void	ft_init_array(int *array, int val, int phils_n);
// void	ft_init_array(int *array, int val);
void	ft_init_data(char **av, t_data *data);

/*		ft_exit.c	*/
void	ft_exit(char *str, t_data *data);

/*		ft_start.c	*/
void	ft_timestamp(int flag, t_data *data, t_philo *actual, char *str);
void	ft_start(t_data *data);

/*	utils_basic.c	*/
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strlen(char *str);
void	ft_write(int fd, char *str);
int		ft_atoi(char *str);
char	*ft_itoa(int num);
void	ft_write_num(int num);

#endif