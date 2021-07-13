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
	gettimeofday(&ms, NULL);
	printf("%ld,%d ...eating phil: %d/%d\tblocking %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1 , g_data.x +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	if (g_data.fork[ft_next_phil(*actual)] == 2)
		g_data.fork_2[ft_next_phil(*actual)] = 2;
	g_data.fork[ft_next_phil(*actual)] = 2;
	if (g_data.fork[ft_prec_phil(*actual)] == 2)
		g_data.fork_2[ft_prec_phil(*actual)] = 2;
	g_data.fork[ft_prec_phil(*actual)] = 2;
	g_data.fork[*actual] = 1;
	if (g_data.die[*actual] != 0)
		g_data.die[*actual]++;
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.eat_t);
	if (g_data.x == 666)
		return ;
	pthread_mutex_lock(g_data.mut);
	gettimeofday(&ms, NULL);
	printf("%ld,%d\t sleeping phil: %d\tfreeing %d_%d\n", ms.tv_sec, ms.tv_usec, *actual +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	if (g_data.fork_2[ft_next_phil(*actual)] == 0)
		g_data.fork[ft_next_phil(*actual)] = 0;
	g_data.fork_2[ft_next_phil(*actual)] = 0;
	if (g_data.fork_2[ft_prec_phil(*actual)] == 0)
		g_data.fork[ft_prec_phil(*actual)] = 0;
	g_data.fork_2[ft_prec_phil(*actual)] = 0;
	if (*actual == g_data.x)
		g_data.x = ft_next_phil(g_data.x);
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.sleep_t);
	if (g_data.x == 666)
		return ;
	pthread_mutex_lock(g_data.mut);
	g_data.die[*actual]++;
	gettimeofday(&ms, NULL);
	printf("%ld,%d\t  thinking phil: %d\n", ms.tv_sec, ms.tv_usec, *actual +1);
	if (g_data.fork[*actual] != 2 && g_data.fork_2[*actual] != 2)
		g_data.fork[*actual] = 0;
	pthread_mutex_unlock(g_data.mut);

}

void	*ft_dying(void *arg)
{
	int				*actual;
	int				x;
	struct timeval	ms;


	actual = (int *)arg;
	while (g_data.fork[g_data.x] < 0)
		continue ;
	while (g_data.x != 666)
	{
		if (g_data.die[*actual] % 2)
		{
			x = g_data.die[*actual];
			usleep(g_data.die_t - g_data.sleep_t);
			if (g_data.die[*actual] == x)
			{
				gettimeofday(&ms, NULL);
				printf("%ld,%d +++ PHILO %d DIED +++\n\n", ms.tv_sec, ms.tv_usec, *actual + 1);
				g_data.x = 666;
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
	printf("seated phil: %d/%d\n", (*(actual)) + 1, g_data.x + 1);
	while (g_data.fork[g_data.x] < 0)
		wait++;
	if (*actual == g_data.x)
		ft_eat_2(actual);
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
			ft_exit("Error: a philo didn't seat", g_data);
		if (pthread_create(&g_data->dying_phil[x], NULL, ft_dying, (void *)&arg[x]) != 0)
			ft_exit("Error: a philo didn't seat", g_data);
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
		if (pthread_join(g_data->dying_phil[x], NULL) != 0)
			printf("\tp_j:error\n");
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
