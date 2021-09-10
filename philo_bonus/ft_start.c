/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/10 18:25:53 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

// void	ft_eat_sleep_think(t_philo	*actual)
// {
	// if (ft_thinking(actual))
	// 	return ;
	// pthread_mutex_lock(actual->fork_r);
	// *actual->f_r_stat = 1;
	// ft_timestamp(0, actual->data, actual, " has taken a fork\n");
	// pthread_mutex_lock(actual->fork_l);
	// *actual->f_l_stat = 1;
	// if (ft_timestamp(0, actual->data, actual, " has taken a fork\n"))
	// 	return (ft_mut_fork(0, actual));
	// if (ft_timestamp(-1, actual->data, actual, "\033[0;32m is eating\033[0m\n"))
	// 	return (ft_mut_fork(0, actual));
	// if (ft_usleep(-1, actual, actual->data))
	// 	return (ft_mut_fork(0, actual));
	// actual->eat_n--;
	// if (ft_timestamp(-2, actual->data, actual, " is sleeping\n"))
	// 	return (ft_mut_fork(0, actual));
	// *actual->f_r_stat = 0;
	// pthread_mutex_unlock(actual->fork_r);
	// *actual->f_l_stat = 0;
	// pthread_mutex_unlock(actual->fork_l);
	// if (ft_usleep(-2, actual, actual->data))
	// 	return ;
// }

long	ft_thinking222(t_philo *actual, sem_t *semaphore)
{
	struct timeval	ms;
	long			x;

	if (actual->data->die_all == 666
		|| ft_timestamp(0, actual->data, actual, " is thinking\n"))
		return (666);
	while (sem_wait(semaphore))
	{
		// sem_wait(semaphore);
		// printf("zzz\n");
		gettimeofday(&ms, NULL);
		x = ms.tv_sec % 1000 * 1000 + ms.tv_usec / 1000;
		if (x - actual->last_eat > actual->data->die_t / 1000)
		{
			// sem_wait(die_sem);
			// pthread_mutex_lock(&actual->data->mut_print);
			return (ft_dead(x - actual->data->start, actual, actual->data));
		}
	}
	return (0);
}

void	ft_eat_sleep_think(t_philo *actual, sem_t *semaphore)
{
	// printf("%ld eat_sleep_think\t%ld\n", actual->name, actual->eat_n);
	// int x = 999;
	// printf("sem_value: %d\t", sem_getvalue(semaphore, &x));
	// printf("%d\n", x);
	if (ft_thinking222(actual, semaphore))
		return ;
	// printf("sem_wait[%ld]:%d\n", actual->name, sem_wait(semaphore));
	// if (sem_wait(semaphore) < 0)
	// {
	// 	printf("sem_wait failed\n");
	// 	return ;
	// }
	// if (sem_wait(semaphore) < 0)
	// {
	// 	printf("sem_wait failed\n");
	// 	return ;
	// }
	if (ft_timestamp(0, actual->data, actual, " has taken a fork\n"))
		return ;
	if (ft_timestamp(0, actual->data, actual, " has taken a fork\n"))
		return ;
	if (ft_timestamp(-1, actual->data, actual, "\033[0;32m is eating\033[0m\n"))
		return ;
	if (ft_usleep(-1, actual, actual->data))
		return ;
	actual->eat_n--;
	if (sem_post(semaphore) < 0)// || sem_post(semaphore) < 0)
	{
		printf("sem_post failed\n");
		return ;
	}
	// if (sem_post(semaphore) < 0)
	// {
	// 	printf("sem_post failed\n");
	// 	return ;
	// }
}



void	ft_routine(t_philo	*philos, int actual)
{
	sem_t	*semaphore;
	// sem_t	*die_sem;

	semaphore = sem_open("forks", O_RDWR);
	philos[actual].die_sem = sem_open("die", O_RDWR);
	if (semaphore == SEM_FAILED || philos[actual].die_sem == SEM_FAILED)
	{
		free(philos);
		ft_exit("sem_open failed child\n", philos[actual].data);
	}
	while (philos[actual].eat_n != 0 && philos[actual].data->die_all != 666)
		ft_eat_sleep_think(&philos[actual], semaphore);
	printf("ended while\n");
	if (sem_close(semaphore) < 0 || sem_close(philos[actual].die_sem) < 0)
	{
		free(philos);
		ft_exit("sem_close failed child\n", philos[actual].data);
	}
	if (philos[actual].data->die_all == 666)
	{
		free(philos);
		exit(1);
	}
	free(philos);
	exit(0);
}

void	ft_start(t_data *data)
{
	t_philo	*philos;
	sem_t	*semaphore;
	sem_t	*die_sem;
	int		x;
	int		*ret;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->phils_n);
	semaphore = sem_open("forks", O_CREAT | O_EXCL, 0777, data->phils_n / 2);
	die_sem = sem_open("die", O_CREAT | O_EXCL, 0777, 1);
	if (semaphore == SEM_FAILED || die_sem == SEM_FAILED)
	{
		free(philos);
		ft_exit("sem_open failed parent\n", data);
	}
	if (sem_close(semaphore) < 0 || sem_close(die_sem) < 0)
		ft_exit("sem_close failed\n", data);
	x = 0;
	while (x < data->phils_n)
	{
		philos[x].name = x + 1;
		philos[x].eat_n = data->eat_n;
		philos[x].last_eat = data->start;
		philos[x].last_sleep = data->start;
		philos[x].data = data;
		philos[x].phid = fork();
		if (philos[x].phid < 0)
		{
			free(philos);
			ft_exit("Philo failed to seat\n", data);
		}
		else if (philos[x].phid == 0)
		{
			ft_routine(philos, x);
		}
		x++;
	}
	ret = (int *)malloc(sizeof(int) * data->phils_n);
	x = 0;
	while (x < data->phils_n)
	{
		waitpid(philos[x].phid, &ret[x], 0);
		// printf("ret[%d]= %d\n", x, ret[x]);
		// if (ret[x] != 0)
		// {
		// // 	if (sem_unlink("forks") < 0)
		// // 		ft_exit("sem_unlink failed\n", data);
		// // 	ft_kill(philos, x, data);
		// 	free(philos);
		// 	exit(1);
		// 	// return ;
		// }
		x++;
	}
	x = 0;
	while (x < data->phils_n)
	{
		printf("ret:%d\n", ret[x]);
		if (ret[x] != 1)
			break ;
		x++;
	}
	if (x == data->phils_n)
		ft_write(1, "\033[0;36mphilos are full!\033[0m\n");
	// ft_check_eat(data, philos); // no-sense con i fork che hanno una propria memoria
	free(philos);
	// if (sem_close(semaphore) < 0)
	// 	ft_exit("sem_close failed\n", data);
	if (sem_unlink("forks") < 0 || sem_unlink("die") < 0)
		ft_exit("sem_unlink failed\n", data);
	printf("unlinked sem\n");
}

// void	*ft_alone(t_philo *actual)
// {
// 	struct timeval	ms;
// 	long			x;

// 	*actual->f_r_stat = 1;
// 	if (ft_timestamp(0, actual->data, actual, " has taken a fork\n"))
// 		return (NULL);
// 	while (*actual->f_r_stat == 1)
// 	{
// 		gettimeofday(&ms, NULL);
// 		x = ms.tv_sec % 1000 * 1000 + ms.tv_usec / 1000;
// 		x -= actual->last_eat;
// 		if (x > actual->data->die_t / 1000)
// 		{
// 			actual->data->die_all = 666;
// 			printf("\033[0;31m%ld %ld died +\033[0m\n", x, actual->name);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }	

// void	*ft_routine(void *arg)
// {
// 	t_philo			*actual;

// 	actual = (t_philo *)arg;
// 	if (actual->name % 2 == 0)
// 		usleep(actual->data->eat_t - 10);
// 	if (actual->data->phils_n == 1)
// 		return (ft_alone(actual));
// 	while (actual->eat_n != 0 && actual->data->die_all != 666)
// 		ft_eat_sleep_think(actual);
// 	return (NULL);
// }

// void	ft_create_philo(t_philo **philos, long *fork,
// 		pthread_mutex_t *mut_fork, t_data *data)
// {
// 	long	x;

// 	x = 0;
// 	while (x < data->phils_n)
// 	{
// 		philos[x] = (t_philo *)malloc(sizeof(t_philo) * 1);
// 		philos[x]->phil = (pthread_t *)malloc(sizeof(pthread_t) * 1);
// 		philos[x]->name = x + 1;
// 		philos[x]->eat_n = data->eat_n;
// 		philos[x]->last_eat = data->start;
// 		philos[x]->last_sleep = data->start;
// 		philos[x]->f_l_stat = &fork[x];
// 		philos[x]->fork_l = &mut_fork[x];
// 		philos[x]->f_r_stat = &fork[ft_next_phil(x, data->phils_n)];
// 		philos[x]->fork_r = &mut_fork[ft_next_phil(x, data->phils_n)];
// 		philos[x]->data = data;
// 		if (pthread_create(philos[x]->phil, NULL,
// 				ft_routine, (void *)philos[x]) != 0)
// 		{
// 			ft_free(fork, philos, mut_fork, data);
// 			ft_exit("Error: a philo didn't seat\n", data);
// 		}			
// 		x++;
// 	}
// }

// void	ft_start(t_data *data)
// {
	// long			x;
	// long			*fork;
	// t_philo			**philos;
	// pthread_mutex_t	*mut_fork;

	// fork = (long *)malloc(sizeof(long) * data->phils_n);
	// ft_init_array(fork, 0, data->phils_n);
	// philos = (t_philo **)malloc(sizeof(t_philo *) * data->phils_n);
	// mut_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
	// 		* (data->phils_n));
	// x = 0;
	// while (x < data->phils_n)
	// 	pthread_mutex_init(&mut_fork[x++], NULL);
	// pthread_mutex_init(&data->mut_die, NULL);
	// pthread_mutex_init(&data->mut_print, NULL);
	// ft_create_philo(philos, fork, mut_fork, data);
	// ft_join_philo(philos, fork, mut_fork, data);
	// ft_check_eat(data, philos);
	// x = 0;
	// while (x < data->phils_n)
	// 	pthread_mutex_destroy(&mut_fork[x++]);
	// pthread_mutex_destroy(&data->mut_die);
	// pthread_mutex_destroy(&data->mut_print);
	// ft_free(fork, philos, mut_fork, data);
// }
