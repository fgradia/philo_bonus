/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:18 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/10 15:17:23 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	ft_next_phil(long actual, long phils_n)
{
	if (actual + 1 < phils_n)
		return (actual + 1);
	return (0);
}

void	ft_init_array(long *array, long val, long phils_n)
{
	long	x;

	x = 0;
	while (x < phils_n)
		array[x++] = val;
}

void	ft_init_data(char **av, t_data *data)
{
	data->phils_n = ft_atoi(av[1]);
	data->die_t = ft_atoi(av[2]) * 1000;
	if (data->die_t == 0)
		data->die_t = 1000;
	data->eat_t = ft_atoi(av[3]) * 1000;
	if (data->eat_t == 0)
		data->eat_t = 1000;
	data->sleep_t = ft_atoi(av[4]) * 1000;
	if (data->sleep_t == 0)
		data->sleep_t = 1000;
	data->eat_n = -1;
	data->die_all = 0;
}

int	main(int ac, char **av)
{
	struct timeval	ms_start;
	t_data			data;

	gettimeofday(&ms_start, NULL);
	if (ac == 5 || ac == 6)
	{
		data.start = ms_start.tv_sec % 1000 * 1000 + ms_start.tv_usec / 1000;
		ft_init_data(av, &data);
		if (ac == 6)
			data.eat_n = ft_atoi(av[5]);
		if (data.phils_n)
			ft_start(&data);
	}
	else
		ft_write(1, "invalid args!\n");
	ft_exit("", &data);
}
