/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:33 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/21 17:13:31 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	ft_thinking(t_philo *actual)
{
	if (actual->die == 666)
		return (666);
	//return (ft_timestamp(0, actual->data, actual, " is thinking\n"));
	if (ft_timestamp(0, actual->data, actual, " is thinking\n") == 666)
		return (666);
	// while (*actual->f_l_stat == 1 || *actual->f_r_stat == 1)
	// {
	// 	ft_mut_fork(0, actual);
	// 	ft_mut_fork(1, actual);
	// 	continue ;
	// }
	// ft_mut_fork(0, actual);
	return (0);

}

long	ft_sleeping(t_philo *actual)
{
	if (actual->die == 666)
		return (666);
	if (ft_timestamp(-2, actual->data, actual, " is sleeping\n") == 666)
		return (666);
	*actual->f_l_stat = 0;
	*actual->f_r_stat = 0;
	return (0);
}

long	ft_forking_eating(t_philo	*actual)
{
	if (actual->die == 666)
		return (666);
	if (*actual->f_l_stat == 1 || *actual->f_r_stat == 1)
	{
		ft_write(1, "\t\tstealing fork...\n");
		actual->die = 666;
		return (666);
	}
	*actual->f_l_stat = 1;
	if (ft_timestamp(0, actual->data, actual, " has taken a fork\n") == 666)
		return (666);
	*actual->f_r_stat = 1;
	if (ft_timestamp(0, actual->data, actual, " has taken a fork\n") == 666)
		return (666);
	return (ft_timestamp(-1, actual->data, actual, " is eating\n"));
}

void	ft_free(long *fork, t_philo **philos,
		pthread_mutex_t *mut_fork, t_data *data)
{
	int	x;

	x = 0;
	while (x < data->phils_n)
	{
		free(philos[x]->phil);
		free(philos[x++]);
	}
	free(philos);
	free(fork);
	free(mut_fork);
}

void	ft_exit(char *str, t_data *data)
{
	ft_write(2, str);
	ft_write(2, "\n");
	exit(0);
	(void)data;
}
