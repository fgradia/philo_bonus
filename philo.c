/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:18 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/17 14:39:03 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_prec_phil(int actual, int phils_n)
{
	if (actual - 1 >= 0)
		return (actual - 1);
	return (phils_n - 1);
}

int	ft_next_phil(int actual, int phils_n)
{
	if (actual + 1 < phils_n)
		return (actual + 1);
	return (0);
}

void	ft_init_array(int *array, int val, int phils_n)
{
	int	x;

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
	// data->eat_n = (int *)malloc(sizeof(int) * data->phils_n);
	// ft_init_array(data->eat_n, -1);	
	// data->x = 0;
	// data->fork = (int *)malloc(sizeof(int) * data->phils_n);
	// ft_init_array(data->fork, 0, data->phils_n);
	// data->fork_2 = (int *)malloc(sizeof(int) * data->phils_n);
	// ft_init_array(data->fork_2, 0);
	// data->die = (int *)malloc(sizeof(int) * data->phils_n);
	// ft_init_array(data->die, -1);
	// data->phil = (pthread_t *)malloc(sizeof(pthread_t) * (data->phils_n));
	// data->dying_phil = (pthread_t *)malloc(sizeof(pthread_t) * (data->phils_n));
	// data->mut_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->phils_n));
	// data->mut_die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	// if (/*!data->phil ||*/ !data->mut_fork /*|| !data->fork*/)
		// ft_exit("malloc_fault\n", data);
	// gettimeofday(&data->ms_start, NULL);
}

int	main(int ac, char **av)
{
	struct timeval	ms_start;
	t_data	data;

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
			data.eat_n = ft_atoi(av[5]);// * data.phils_n;
			// ft_init_array(data.eat_n, ft_atoi(av[5]));
		if (data.phils_n == 1)
		{
			data.phils_n--;
			ft_timestamp(0, &data, NULL, " died +++\n");
			// ft_write(1, " died +++\n");
			ft_exit("", &data);
		}
		ft_start(&data);
	}
	else
		exit(2);
	ft_exit("", &data);
}
