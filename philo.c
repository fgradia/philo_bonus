/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:18 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 10:17:54 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	ft_prec_phil(long actual, long phils_n)
{
	if (actual - 1 >= 0)
		return (actual - 1);
	return (phils_n - 1);
}

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
	data->eat_t = ft_atoi(av[3]) * 1000;
	data->sleep_t = ft_atoi(av[4]) * 1000;
	data->eat_n = -1;
}

int	main(int ac, char **av)
{
	struct timeval	ms_start;
	t_data			data;

	gettimeofday(&ms_start, NULL);
	if (ac == 5 || ac == 6)
	{
		data.start = (ms_start.tv_sec % 1000) * 1000000 + ms_start.tv_usec;
		ft_write_num(data.start / 1000000);
		ft_write(1, ",");
		ft_write_num(data.start % 1000000);
		ft_write(1, "\n");
		ft_init_data(av, &data);
		if (ac == 6)
			data.eat_n = ft_atoi(av[5]);
		if (data.phils_n == 1)
		{
			data.phils_n--;
			ft_timestamp(0, &data, NULL, " died +++\n");
			ft_exit("", &data);
		}
		ft_start(&data);
	}
	else
		exit(2);
	ft_exit("", &data);
}
