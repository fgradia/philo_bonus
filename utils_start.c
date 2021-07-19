/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:47:10 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 15:49:34 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_mut_fork(long status, t_philo	*actual)
{
	if (status)
	{
		pthread_mutex_lock(actual->fork_l);
		pthread_mutex_lock(actual->fork_r);
	}
	else
	{
		pthread_mutex_unlock(actual->fork_r);
		pthread_mutex_unlock(actual->fork_l);
	}
}

long	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str)
{
	long			x;
	struct timeval	ms;

	gettimeofday(&ms, NULL);
	x = ms.tv_sec % 1000 * 1000 + ms.tv_usec / 1000;
	pthread_mutex_lock(&data->mut_die);
	ft_write_num((x - data->start));
	ft_write(1, " ");
	if (!actual)
		ft_write_num(flag - 1);
	else
		ft_write_num(actual->name);
	if (actual && x - actual->last_eat > data->die_t / 1000)
	{
		ft_write(1, " \t\t\tdied +++\n");
		actual->die = 666;
		pthread_mutex_unlock(&data->mut_die);
		return (666);
	}
	else
		ft_write(1, str);
	if (flag == 1)
		actual->last_eat = x;
	pthread_mutex_unlock(&data->mut_die);
	return (0);
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
