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

typedef struct s_table
{
	pthread_t		*actual;
	char			status;
	struct s_table	*prev;
	struct s_table	*next;
	// struct s_table	
}	t_table;

typedef struct s_data
{
	int				phils_n;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_n;
	int				x;
	int				*fork_2;
	int				*fork;			//	0 == disponibile ; 1 == eating ; 2 == blocked 
	int				*die;			//	pari == ha mangiato ; dispari == inattivo 
	pthread_t		*phil;
	pthread_t		*dying_phil;
	pthread_mutex_t	*mut;

}	t_data;

t_data	g_data;

/*		philo.c		****	MAIN	****	*/
int		ft_prec_phil(int actual);
int		ft_next_phil(int actual);
void	ft_init_array(int *array);
void	ft_init_data(char **av, t_data *g_data);

/*		ft_exit.c	*/
void	ft_exit(char *str, t_data *g_data);

/*		ft_start.c	*/
void	ft_start(t_data *g_data);

/*	utils_basic.c	*/
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strlen(char *str);
void	ft_write(int fd, char *str);
int		ft_atoi(char *str);
char	*ft_itoa(int num);

#endif