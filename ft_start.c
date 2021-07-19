/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 11:28:41 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str)
{
	long				x;
	long				pow;
	struct timeval	ms;

	gettimeofday(&ms, NULL);
	pow = 1000000;
	x = (ms.tv_sec % 1000) * pow + ms.tv_usec;
	ft_write_num((x - data->start) / pow);
	ft_write(1, ",");
	x = ms.tv_usec + pow  - (data->start % pow);
	if (x / pow != 0)
		x = x % pow;
	pow /= 10;
	while (x / pow == 0)
	{
		ft_write_num(0);
		pow /= 10;
	}
	ft_write_num((x));// / 100));
	ft_write(1, " ");
	if (!actual)
	{
		ft_write(1, " died --+++\n");
		return (666);
	}
	else
		ft_write_num(actual->name);
	if ((x / 1000) - (actual->last_eat / 1000) > data->die_t / 1000)
	{
		ft_write(1, " \t\t\tdied +++\n");
		actual->die = 666;
		return (666);
	}
	else
		ft_write(1, str);
	if (flag == 1)
		actual->last_eat = x;
	return (0);
}

void	ft_mut_fork(long status, t_philo	*actual)
{
	if (status)
	{
		pthread_mutex_lock(actual->fork_l);
		pthread_mutex_lock(actual->fork_r);
		pthread_mutex_lock(&actual->data->mut_die);
	}
	else
	{
		pthread_mutex_unlock(&actual->data->mut_die);
		pthread_mutex_unlock(actual->fork_r);
		pthread_mutex_unlock(actual->fork_l);
	}
}

void	ft_eat(t_philo	*actual)
{
	ft_mut_fork(1, actual);
	// if (*actual->f_l_stat != 0 && *actual->f_r_stat != 0)
	// 	return (ft_mut_fork(0, actual));
	// if (ft_forking('l', actual) == 666)
		// return (ft_mut_fork(0, actual));
	// if (ft_forking('r', actual) == 666)
		// return (ft_mut_fork(0, actual));
	if (ft_forking_2(actual) == 666)
		return (ft_mut_fork(0, actual));
	// if (ft_timestamp(1, actual->data, actual, " is eating\n") == 666)
	// 	return (ft_mut_fork(0, actual));
	actual->eat_n--;
	pthread_mutex_unlock(&actual->data->mut_die);
	usleep(actual->data->eat_t);
	pthread_mutex_lock(&actual->data->mut_die);
	if (ft_sleeping(actual) == 666)
		return (ft_mut_fork(0, actual));
	ft_mut_fork(0, actual);
	usleep(actual->data->sleep_t);
	ft_mut_fork(1, actual);
	if (ft_thinking(actual) == 666)
		return (ft_mut_fork(0, actual));
	ft_mut_fork(0, actual);
}

void	*ft_routine(void *arg)
{
	t_philo			*actual;

	actual = (t_philo *)arg;
	if (actual->name % 2 == 0)
		usleep(actual->data->eat_t - 10);
	while (actual->eat_n != 0 && actual->die != 666)
	{
		ft_eat(actual);
	}
	actual->die = 666;
	return (NULL);
}

void	ft_lets_die(long flag, t_philo **philos, t_data *data)
{
	long	x;

	x = 0;
	while (flag && x < data->phils_n)
	{
		if (philos[x]->eat_n != 0)
			break ;
		x++;
	}
	if (x == data->phils_n)
	{
		ft_write(1, "hanno mangiato tutti\n");
		return ;
	}
	x = 0;
	while (1)
	{
		// pthread_mutex_lock(&data->mut_die);
		if (philos[x]->die == 666)
			break ;
		// pthread_mutex_unlock(&data->mut_die);
		x = ft_next_phil(x, data->phils_n);
	}
	x = 0;
	while (x < data->phils_n)
	{
		philos[x]->die = 666;
		x++;
	}
	// pthread_mutex_unlock(&data->mut_die);
}

void	ft_create_philo(t_philo **philos, long *fork, pthread_mutex_t *mut_fork, t_data *data)
{
	long	x;

	x = 0;
	while (x < data->phils_n)
	{
		philos[x] = (t_philo *)malloc(sizeof(t_philo) * 1);
		philos[x]->phil = (pthread_t *)malloc(sizeof(pthread_t) * 1);
		philos[x]->name = x + 1;
		philos[x]->eat_n = data->eat_n;
		philos[x]->last_eat = data->start;
		philos[x]->die = 0;
		philos[x]->f_l_stat = &fork[x];
		philos[x]->fork_l = &mut_fork[x];
		philos[x]->f_r_stat = &fork[ft_next_phil(x, data->phils_n)];
		philos[x]->fork_r = &mut_fork[ft_next_phil(x, data->phils_n)];
		philos[x]->data = data;
		if (pthread_create(philos[x]->phil, NULL, ft_routine, (void *)philos[x]) != 0)
			ft_exit("Error: a philo didn't seat\n", data);
		x++;
	}
	ft_lets_die(1, philos, data);
}

void	ft_join_philo(t_philo **philos, t_data *data)
{
	long	x;

	x = 0;
	while (x < data->phils_n)
	{
		if (pthread_join(*philos[x]->phil, NULL) != 0)
			ft_write(1, "\tp_j:error\n");
		x++;
	}
}

void	ft_start(t_data *data)
{
	long			x;
	long			*fork;
	t_philo			**philos;
	pthread_mutex_t	*mut_fork;

	fork = (long *)malloc(sizeof(long) * data->phils_n);
	ft_init_array(fork, 0, data->phils_n);
	philos = (t_philo **)malloc(sizeof(t_philo *) * data->phils_n);
	mut_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->phils_n));
	x = 0;
	while (x < data->phils_n)
	{
	 	pthread_mutex_init(&mut_fork[x], NULL);
		x++;
	}
	pthread_mutex_init(&data->mut_die, NULL);
	ft_create_philo(philos, fork, mut_fork, data);
	ft_join_philo(philos, data);
	ft_lets_die(1, philos, data);
	x = 0;
	while (x < data->phils_n)
	{
		pthread_mutex_destroy(&mut_fork[x]);
		x++;
	}
	pthread_mutex_destroy(&data->mut_die);
	free(fork);
	x = 0;
	while (x < data->phils_n)
	{
		free(philos[x]->phil);
		free(philos[x]);
		x++;
	}
	free(philos);
	free(mut_fork);
}
