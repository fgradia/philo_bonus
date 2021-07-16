/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/16 18:52:12 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

// // void	ft_timestamp(int *actual)
// {
// 	int				x;
// 	int				pow;
// 	struct timeval	ms;

// 	pow = 1000000;
// 	gettimeofday(&ms, NULL);
// 	x = (ms.tv_sec % 1000) * pow + ms.tv_usec;
// 	// ft_write_num(ms.tv_sec - g_data.ms_start.tv_sec);
// 	ft_write_num((x - g_data.start) / pow);
// 	ft_write(1, ",");
// 	x = ms.tv_usec + pow  - g_data.ms_start.tv_usec;
// 	if (x / pow != 0)
// 		x = x % pow;
// 	pow /= 10;
// 	while (x / pow == 0)
// 	{
// 		ft_write_num(0);
// 		pow /= 10;
// 	}
// 	// if (x / 1000000)
// 	ft_write_num((x / 100));// - g_data.start) % pow);
// 	ft_write(1, " ");
// 	ft_write_num(*actual + 1);
// 	// ft_write(1, " has taken a fork\n");
// }

void	ft_eat_2(int *actual)
{
	// struct timeval	ms;
	// if (g_data.eat_n[*actual] < g_data.eat_n[ft_next_phil(g_data.x)])
	pthread_mutex_lock(g_data.mut);
	if (g_data.fork[*actual] != 0 || g_data.fork[ft_next_phil(*actual)] != 0
		|| g_data.eat_n[*actual] < g_data.eat_n[ft_next_phil(*actual)] || g_data.eat_n[*actual] < g_data.eat_n[ft_prec_phil(*actual)])
	{
		pthread_mutex_unlock(g_data.mut);
		return ;
	}
	pthread_mutex_unlock(g_data.mut);
	// if (g_data.fork[ft_next_phil(*actual)] == 2)
		// g_data.fork_2[ft_next_phil(*actual)] = 2;
	pthread_mutex_lock(&g_data.mut_fork[ft_next_phil(*actual)]);
	g_data.fork[ft_next_phil(*actual)] = 2;
	pthread_mutex_unlock(&g_data.mut_fork[ft_next_phil(*actual)]);
	pthread_mutex_lock(g_data.mut);

	ft_timestamp(/*ms,*/ actual);
	ft_write(1, " has taken a fork\n");
	// printf("%ld,%d ...eating phil: %d/%d\tblocking %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1 , g_data.x +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);

	pthread_mutex_unlock(g_data.mut);

	// if (g_data.fork[ft_prec_phil(*actual)] == 2)
		// g_data.fork_2[ft_prec_phil(*actual)] = 2;
	// g_data.fork[ft_prec_phil(*actual)] = 2;
	pthread_mutex_lock(&g_data.mut_fork[(*actual)]);
	g_data.fork[*actual] = 1;
	pthread_mutex_unlock(&g_data.mut_fork[(*actual)]);
	pthread_mutex_lock(g_data.mut);
	ft_timestamp(/*ms,*/ actual);
	ft_write(1, " has taken a fork\n");
	// if (g_data.die[*actual] != 0)
	ft_timestamp(/*ms,*/ actual);
	ft_write(1, " is eating\n");
	g_data.die[*actual]++;
	g_data.eat_n[*actual]--;
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.eat_t);
	if (g_data.x == 666)// || g_data.eat_n[*actual] == 0)
		return ;
	pthread_mutex_lock(g_data.mut);
	g_data.die[*actual]++;
	pthread_mutex_unlock(g_data.mut);
	// gettimeofday(&ms, NULL);
	// printf("%ld,%d\t sleeping phil: %d\tfreeing %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	// if (g_data.fork_2[ft_next_phil(*actual)] == 0)
		// g_data.fork[ft_next_phil(*actual)] = 0;
	pthread_mutex_lock(&g_data.mut_fork[ft_next_phil(*actual)]);
	g_data.fork[ft_next_phil(*actual)] = 0;
	pthread_mutex_unlock(&g_data.mut_fork[ft_next_phil(*actual)]);
	pthread_mutex_lock(&g_data.mut_fork[(*actual)]);
	// if (g_data.fork[*actual] != 2)// && g_data.fork_2[*actual] != 2)
		g_data.fork[*actual] = 0;
	pthread_mutex_unlock(&g_data.mut_fork[(*actual)]);
	// g_data.fork_2[ft_next_phil(*actual)] = 0;
	// if (g_data.fork_2[ft_prec_phil(*actual)] == 0)
		// g_data.fork[ft_prec_phil(*actual)] = 0;
	// g_data.fork_2[ft_prec_phil(*actual)] = 0;
	pthread_mutex_lock(g_data.mut);
	if (*actual == g_data.x)
		g_data.x = ft_next_phil(g_data.x);
	ft_timestamp(/*ms,*/ actual);
	ft_write(1, " is sleeping\n");
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.sleep_t);
	pthread_mutex_lock(g_data.mut);
	if (g_data.x == 666 || g_data.eat_n[*actual] == 0 || g_data.fork[*actual] == 0)
	{
		pthread_mutex_unlock(g_data.mut);
		return ;
	}
	ft_timestamp(/*ms,*/ actual);
	ft_write(1, " is thinking\n");
	// g_data.die[*actual]++;
	// gettimeofday(&ms, NULL);
	// printf("%ld,%d\t  thinking phil: %d\n", ms.tv_sec, ms.tv_usec, *actual +1);
	pthread_mutex_unlock(g_data.mut);

}

void	*ft_dying(void *arg)
{
	int				*actual;
	int				x;
	// struct timeval	ms;

	x = 0;
	actual = (int *)arg;
	// while (g_data.fork[g_data.x] <= 0)
	while (g_data.die[g_data.x] < 1)
		x++;//continue ;
	while (g_data.x != 666 && g_data.eat_n[*actual] != 0)
	{
		if (g_data.die[*actual] % 2 && g_data.die[*actual] != -1)
		{
			x = g_data.die[*actual];
			usleep(g_data.die_t);// - g_data.sleep_t);
			if (g_data.die[*actual] == x && g_data.x != 666 && g_data.eat_n[*actual] != 0)// && !gettimeofday(&ms, NULL))
			{
				pthread_mutex_lock(g_data.mut);
				g_data.x = 666;
				g_data.eat_n[*actual] = 0;
				ft_timestamp(/*ms,*/ actual);
				ft_write(1, " died +++\n");
				pthread_mutex_unlock(g_data.mut);
				return (NULL);
			}	
		}
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	int	*actual;

	actual = (int *)arg;
	while (g_data.eat_n[*actual] != 0)
	{
				
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
	int	x;

	args = (int *)malloc(sizeof(int) * g_data->phils_n);
	x = 0;
	while (x < g_data->phils_n)
	{
	 	pthread_mutex_init(&g_data->mut_fork[x], NULL);
		x++;
	}
	pthread_mutex_init(g_data->mut, NULL);
	g_data->fork[g_data->x] = -1;
	ft_create_philo(args, g_data);
	g_data->fork[g_data->x] = 0;
	ft_join_philo(g_data);
	free(args);
	x = 0;
	while (x < g_data->phils_n)
	{
		pthread_mutex_destroy(&g_data->mut_fork[x]);
		x++;
	}
	pthread_mutex_destroy(g_data->mut);
}
