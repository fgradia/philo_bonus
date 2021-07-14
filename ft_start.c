/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/14 16:47:08 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_eat_2(int *actual)
{
	struct timeval	ms;

	pthread_mutex_lock(g_data.mut);
	if (g_data.fork[*actual] != 0)
	{
		pthread_mutex_unlock(g_data.mut);
		return ;
	}
	if (g_data.fork[ft_next_phil(*actual)] == 2)
		g_data.fork_2[ft_next_phil(*actual)] = 2;
	g_data.fork[ft_next_phil(*actual)] = 2;
	gettimeofday(&ms, NULL);
	ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
	ft_write(1, " ");
	ft_write_num(*actual + 1);
	ft_write(1, " has taken a fork\n");
	// printf("%ld,%d ...eating phil: %d/%d\tblocking %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1 , g_data.x +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	if (g_data.fork[ft_prec_phil(*actual)] == 2)
		g_data.fork_2[ft_prec_phil(*actual)] = 2;
	g_data.fork[ft_prec_phil(*actual)] = 2;
	gettimeofday(&ms, NULL);
	ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
	ft_write(1, " ");
	ft_write_num(*actual + 1);
	ft_write(1, " has taken a fork\n");
	g_data.fork[*actual] = 1;
	// if (g_data.die[*actual] != 0)
		g_data.die[*actual]++;
	gettimeofday(&ms, NULL);
	ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
	ft_write(1, " ");
	ft_write_num(*actual + 1);
	ft_write(1, " is eating\n");
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.eat_t);
	if (g_data.x == 666)
		return ;
	pthread_mutex_lock(g_data.mut);
	g_data.die[*actual]++;
	// gettimeofday(&ms, NULL);
	// printf("%ld,%d\t sleeping phil: %d\tfreeing %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	if (g_data.fork_2[ft_next_phil(*actual)] == 0)
		g_data.fork[ft_next_phil(*actual)] = 0;
	g_data.fork_2[ft_next_phil(*actual)] = 0;
	if (g_data.fork_2[ft_prec_phil(*actual)] == 0)
		g_data.fork[ft_prec_phil(*actual)] = 0;
	g_data.fork_2[ft_prec_phil(*actual)] = 0;
	if (*actual == g_data.x)
		g_data.x = ft_next_phil(g_data.x);
	gettimeofday(&ms, NULL);
	ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
	ft_write(1, " ");
	ft_write_num(*actual + 1);
	ft_write(1, " is sleeping\n");
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.sleep_t);
	if (g_data.x == 666)
		return ;
	pthread_mutex_lock(g_data.mut);
	// g_data.die[*actual]++;
	// gettimeofday(&ms, NULL);
	// printf("%ld,%d\t  thinking phil: %d\n", ms.tv_sec, ms.tv_usec, *actual +1);
	if (g_data.fork[*actual] != 2 && g_data.fork_2[*actual] != 2)
		g_data.fork[*actual] = 0;
	gettimeofday(&ms, NULL);
	ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
	ft_write(1, ",");
	ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
	ft_write(1, " ");
	ft_write_num(*actual + 1);
	ft_write(1, " is thinking\n");
	pthread_mutex_unlock(g_data.mut);

}

void	*ft_dying(void *arg)
{
	int				*actual;
	int				x;
	struct timeval	ms;

	x = 0;
	actual = (int *)arg;
	// while (g_data.fork[g_data.x] <= 0)
	while (g_data.die[g_data.x] < 1)
		x++;//continue ;
	while (g_data.x != 666)
	{
		if (g_data.die[*actual] % 2 && g_data.die[*actual] != -1)
		{
			x = g_data.die[*actual];
			usleep(g_data.die_t);// - g_data.sleep_t);
			if (g_data.die[*actual] == x && g_data.x != 666 && !gettimeofday(&ms, NULL))
			{
				g_data.x = 666;
				// gettimeofday(&ms, NULL);
				ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
				ft_write(1, ",");
				ft_write_num(ms.tv_usec / 1000 - g_data.ms_start.tv_usec / 1000);
				ft_write(1, " ");
				ft_write_num(*actual + 1);
				ft_write(1, " died +++\n");
				// gettimeofday(&ms, NULL);
				// printf("%ld,%d +++ PHILO %d DIED +++\n\n", ms.tv_sec, ms.tv_usec, *actual + 1);
				ft_exit("", &g_data);
				return (NULL);
			}	
		}
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	int	*actual;
	int	wait;

	wait = 0;
	actual = (int *)arg;
	// printf("seated phil: %d/%d\n", (*(actual)) + 1, g_data.x + 1);
	while (g_data.fork[g_data.x] < 0)
		wait++;
	if (*actual == g_data.x)
		ft_eat_2(actual);
	else
		while (g_data.fork[g_data.x] != 1)
			wait++;
	while (g_data.x != 666)
	{
		wait = 0;
		if (*actual == ft_next_phil( g_data.x))
			while (*actual != g_data.x && g_data.x != 666)
				wait++;
		if (g_data.fork[*actual] == 0)
			ft_eat_2(actual);
	}
	return (NULL);
}

void	ft_create_philo(int *arg, t_data *g_data)
{
	int	x;

	x = 0;
	while (x < g_data->phils_n)
	{
		arg[x] = x;
		if (pthread_create(&g_data->phil[x], NULL, ft_routine, (void *)&arg[x]) != 0)
			ft_exit("Error: a philo didn't seat\n", g_data);
		if (pthread_create(&g_data->dying_phil[x], NULL, ft_dying, (void *)&arg[x]) != 0)
			ft_exit("Error: a philo didn't seat\n", g_data);
		if (pthread_detach(g_data->dying_phil[x]))
			printf("\tp_d:error\n");
		x++;
	}
}

void	ft_join_philo(t_data *g_data)
{
	int	x;

	x = 0;
	while (x < g_data->phils_n)
	{
	 	if (pthread_join(g_data->phil[x], NULL) != 0)
			printf("\tp_j:error\n");
		// if (pthread_join(g_data->dying_phil[x], NULL) != 0)
		// 	printf("\tp_j:error\n");
		x++;
	}
}

void	ft_start(t_data *g_data)
{
	int *args;

	args = (int *)malloc(sizeof(int) * g_data->phils_n);
	pthread_mutex_init(g_data->mut, NULL);
	g_data->fork[g_data->x] = -1;
	ft_create_philo(args, g_data);
	g_data->fork[g_data->x] = 0;
	ft_join_philo(g_data);
	free(args);
	pthread_mutex_destroy(g_data->mut);
}
