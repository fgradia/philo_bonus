/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 15:49:26 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_eat_sleep_think(t_philo	*actual)
{
	ft_mut_fork(1, actual);
	if (ft_forking_eating(actual) == 666)
		return (ft_mut_fork(0, actual));
	actual->eat_n--;
	usleep(actual->data->eat_t);
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
		ft_eat_sleep_think(actual);
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
		if (philos[x]->die == 666)
			break ;
		x = ft_next_phil(x, data->phils_n);
	}
	x = 0;
	while (x < data->phils_n)
		philos[x++]->die = 666;
}

void	ft_create_philo(t_philo **philos, long *fork,
		pthread_mutex_t *mut_fork, t_data *data)
{
	long	x;

	x = -1;
	while (x++ < data->phils_n)
		ft_timestamp(x + 2, data, NULL, " is thinking\n");
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
		if (pthread_create(philos[x]->phil, NULL,
				ft_routine, (void *)philos[x]) != 0)
			ft_exit("Error: a philo didn't seat\n", data);
		x++;
	}
	ft_lets_die(1, philos, data);
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
	mut_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (data->phils_n));
	x = 0;
	while (x < data->phils_n)
		pthread_mutex_init(&mut_fork[x++], NULL);
	pthread_mutex_init(&data->mut_die, NULL);
	ft_create_philo(philos, fork, mut_fork, data);
	ft_join_philo(philos, data);
	pthread_mutex_lock(&data->mut_die);
	ft_lets_die(1, philos, data);
	pthread_mutex_unlock(&data->mut_die);
	x = 0;
	while (x < data->phils_n)
		pthread_mutex_destroy(&mut_fork[x++]);
	pthread_mutex_destroy(&data->mut_die);
	ft_free(fork, philos, mut_fork, data);
}
