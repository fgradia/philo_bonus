/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:33 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/15 16:32:41 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_find_phid(t_philo *philos, int x)
{
	int	y;

	y = 0;
	while (x != philos[y].phid)
		y++;
	return (y);
}

void	ft_check_eat(t_philo *philos, t_data *data, int first, int *ret)
{
	int	x;

	x = 0;
	while (x < data->phils_n)
	{
		if (x != first)
			waitpid(philos[x].phid, &ret[x], 0);
		x++;
	}
}

long	ft_thinking222(t_philo *actual, sem_t *semaphore)
{
	struct timeval	ms;
	long			x;

	if (actual->data->die_all == 666
		|| ft_timestamp(0, actual->data, actual, " is thinking\n"))
		return (666);
	sem_wait(semaphore);
	ft_timestamp(0, actual->data, actual, " has taken a fork\n");
	while (sem_wait(semaphore))
	{
		gettimeofday(&ms, NULL);
		x = ms.tv_sec % 1000 * 1000 + ms.tv_usec / 1000;
		if (x - actual->last_eat > actual->data->die_t / 1000)
		{
			return (ft_dead(x - actual->data->start, actual, actual->data));
		}
	}
	ft_timestamp(0, actual->data, actual, " has taken a fork\n");
	return (0);
}

void	ft_kill(t_philo *philos, int x, t_data *data)
{
	int	y;

	y = 0;
	while (y < data->phils_n)
	{
		if (y != x)
			kill((philos)[y].phid, 2);
		y++;
	}
}

void	ft_exit(char *str, t_data *data)
{
	ft_write(2, str);
	exit(1);
	(void)data;
}
