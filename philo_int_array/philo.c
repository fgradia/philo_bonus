/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:18 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/15 10:57:37 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_prec_phil(int actual)
{
	if (actual - 1 >= 0)
		return (actual - 1);
	return (g_data.phils_n - 1);
}

int	ft_next_phil(int actual)
{
	if (actual + 1 < g_data.phils_n)
		return (actual + 1);
	return (0);
}

void	ft_init_array(int *array, int val)
{
	int	x;

	x = 0;
	while (x < g_data.phils_n)
		array[x++] = val;
}

void	ft_init_data(char **av, t_data *g_data)
{
	g_data->phils_n = ft_atoi(av[1]);
	g_data->die_t = ft_atoi(av[2]) * 1000;
	g_data->eat_t = ft_atoi(av[3]) * 1000;
	g_data->sleep_t = ft_atoi(av[4]) * 1000;
	g_data->eat_n = (int *)malloc(sizeof(int) * g_data->phils_n);
	ft_init_array(g_data->eat_n, -1);	// g_data->eat_n = NULL;//-1;
	g_data->x = 0;
	g_data->fork = (int *)malloc(sizeof(int) * g_data->phils_n);
	ft_init_array(g_data->fork, 0);
	g_data->fork_2 = (int *)malloc(sizeof(int) * g_data->phils_n);
	ft_init_array(g_data->fork_2, 0);
	g_data->die = (int *)malloc(sizeof(int) * g_data->phils_n);
	ft_init_array(g_data->die, -1);
	g_data->phil = (pthread_t *)malloc(sizeof(pthread_t) * (g_data->phils_n));
	g_data->dying_phil = (pthread_t *)malloc(sizeof(pthread_t) * (g_data->phils_n));
	g_data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!g_data->phil || !g_data->mut || !g_data->fork)
		ft_exit("malloc_fault\n", g_data);
	// gettimeofday(&g_data->ms_start, NULL);
}

int	main(int ac, char **av)
{
	gettimeofday(&g_data.ms_start, NULL);
	// g_data.ms_start.tv_sec *= 1000000;
	// ft_write_num(g_data.ms_start.tv_sec);
// ft_write(1, "\n");
	// g_data.ms_start.tv_sec += g_data.ms_start.tv_usec;
	ft_write_num(g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(g_data.ms_start.tv_usec);
	ft_write(1, "\t");
	g_data.start = (g_data.ms_start.tv_sec % 1000) * 1000000 + g_data.ms_start.tv_usec;
	ft_write_num(g_data.start / 1000000);
	ft_write(1, ",");
	ft_write_num(g_data.start % 1000000);
	ft_write(1, "\n");


	if (ac == 5 || ac == 6)
	{
		ft_init_data(av, &g_data);
		if (ac == 6)
			ft_init_array(g_data.eat_n, ft_atoi(av[5]));// g_data.eat_n = ft_atoi(av[5]) * g_data.phils_n;
		if (g_data.phils_n == 1)
		{
			g_data.phils_n--;
			ft_timestamp(&g_data.phils_n);
			ft_write(1, " died +++\n");
			ft_exit("", &g_data);
		}
		ft_start(&g_data);
	}
	else
		exit(2);
	ft_exit("", &g_data);
}
