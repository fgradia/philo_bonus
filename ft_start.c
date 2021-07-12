#include "philolib.h"

void	ft_free_matr(char **str)
{
	int	x;

	x = 0;
	while (str[x]) //x < g_data->phils_n)
	{
		free(str[x]);
		x++;
	}
	free(str);
}

void	ft_eat_2(int *actual, int *first)
{
	pthread_mutex_lock(g_data.mut);
	if (g_data.fork[*actual] == 1)
	{
		pthread_mutex_unlock(g_data.mut);
		return ;
	}
	g_data.fork[ft_next_phil(*actual)] = 1;
	g_data.fork[ft_prec_phil(*actual)] = 1;
	g_data.fork[*actual] = 1;
	// *first = 2;
	pthread_mutex_unlock(g_data.mut);
	printf("\teating phil: %d/%d\tblocking %d_%d\n", *actual +1 , g_data.x +1, ft_next_phil(*actual) +1, ft_prec_phil(*actual) + 1);
	usleep(g_data.eat_t);
	// pthread_mutex_lock(g_data.mut);
	g_data.fork[ft_next_phil(*actual)] = 0;
	g_data.fork[ft_prec_phil(*actual)] = 0;
	// pthread_mutex_unlock(g_data.mut);
	printf("\t\tsleeping phil: %d\n", *actual +1);
	// g_data.x = ft_next_phil(g_data.x);
	usleep(g_data.sleep_t);
	// pthread_mutex_lock(g_data.mut);
	g_data.fork[*actual] = 0;
	// pthread_mutex_unlock(g_data.mut);

}
	int first;

void	ft_eat(int *actual, int *first)
{
	pthread_mutex_lock(g_data.mut);
	g_data.fork[ft_next_phil(g_data.x)] = 1;
	g_data.fork[ft_prec_phil(g_data.x)] = 1;
	g_data.fork[g_data.x] = 1;
	printf("\teating phil: %d/%d\tblocking %d_%d\n", *actual +1, g_data.x +1, ft_next_phil(g_data.x) +1, ft_prec_phil(g_data.x) + 1);
	// pthread_mutex_lock(g_data.mut);
	*first = 1;
	pthread_mutex_unlock(g_data.mut);
	// pthread_mutex_unlock(g_data.mut);
	usleep(g_data.eat_t);
	pthread_mutex_lock(g_data.mut);
	g_data.fork[ft_next_phil(g_data.x)] = 0;
	g_data.fork[ft_prec_phil(g_data.x)] = 0;
	printf("\t\tsleeping phil: %d\n", *actual +1);
	g_data.x = ft_next_phil(g_data.x);
	pthread_mutex_unlock(g_data.mut);
	usleep(g_data.sleep_t);
	// pthread_mutex_lock(g_data.mut);
	printf("\t\t\tthinking phil: %d\n", *actual +1);
	g_data.fork[g_data.x] = 0;
	// pthread_mutex_unlock(g_data.mut);

}

void	*ft_routine(void *arg)
{
	int	*actual;
	int	wait;

	wait = 0;
	// first = 0;
	actual = (int *)arg;
	printf("seated phil: %d/%d\n", (*(actual)) + 1, g_data.x + 1);
	while (g_data.fork[g_data.x] < 0)
		wait++;
	while (g_data.x != 666)
	{
		wait = 0;
		if (*actual == g_data.x && g_data.fork[g_data.x] == 0)
		{
			// pthread_mutex_lock(g_data.mut);
			// g_data.fork[ft_next_phil(g_data.x)] = 1;
			// g_data.fork[ft_prec_phil(g_data.x)] = 1;
			// g_data.fork[g_data.x] = 1;
			// pthread_mutex_unlock(g_data.mut);
			// printf("\teating phil: %d - %d\n", *actual, g_data.x);
			// first = 1;
			// usleep(g_data.eat_t); + 1
			// // pthread_mutex_lock(g_data.mut);
			// g_data.fork[ft_next_phil(g_data.x)] = 0;
			// g_data.fork[ft_prec_phil(g_data.x)] = 0;
			// // pthread_mutex_unlock(g_data.mut);
			// printf("\t\tsleeping phil: %d\n", *actual);
			// g_data.x = ft_next_phil(g_data.x);
			// usleep(g_data.sleep_t);
			// // pthread_mutex_lock(g_data.mut);
			// g_data.fork[g_data.x] = 0;
			// // pthread_mutex_unlock(g_data.mut);
			ft_eat(actual, &first);
		}
		else
		{
			// printf("\t\t\tthinking phil: %d\n", *actual +1);
			// else
			while (g_data.fork[g_data.x] != 1)
					wait++;
			while (*actual != g_data.x && /*first != 1 && */g_data.fork[*actual] != 0)
				wait++;
			if (g_data.fork[*actual] == 0)
			{
				ft_eat_2(actual, &first);
				// while (first != 2)
					// wait++;
			}
			// usleep(g_data.sleep_t);
		}
		first = 0;
		printf("\n\n");
	}
	// free(actual);
	return (NULL);
}

void	ft_create_philo(int *arg, t_data *g_data)
{
	int	x;
	// int *arg;//[g_data->phils_n];
	// int *arg;

	// arg = (int *)malloc(sizeof(int) * g_data->phils_n);
	x = 0;


	while (x < g_data->phils_n)
	{
		arg[x] = x;
		// str[x] = ft_itoa(x + 1);
		if (pthread_create(&g_data->phil[x], NULL, ft_routine, (void *)&arg[x]) != 0)
			ft_exit("Error: a philo didn't seat", g_data);
		x++;
	}
	// free(arg);
	
}

void	ft_join_philo(t_data *g_data)
{
	int	x;

	x = 0;
	while (x < g_data->phils_n)
	{
	 	if (pthread_join(g_data->phil[x], NULL) != 0)
			printf("\tp_j:error\n");
		x++;
	}
}

void	ft_start(t_data *g_data)
{
	// char	**str;
	// int		*x;
	int *args;

	// args = NULL;
	args = (int *)malloc(sizeof(int) * g_data->phils_n);
	pthread_mutex_init(g_data->mut, NULL);
	// str = (char **)malloc(sizeof(char *) * (g_data->phils_n + 1));
	// str[g_data->phils_n] = NULL;
	// pthread_mutex_lock(g_data->mut);

	g_data->fork[g_data->x] = -1;
	ft_create_philo(args, g_data);
	g_data->fork[g_data->x] = 0;
	// pthread_mutex_unlock(g_data->mut);

	ft_join_philo(g_data);
	free(args);
	// ft_free_matr(str);
	pthread_mutex_destroy(g_data->mut);
	// x = 0;
	// while (x < g_data->phils_n)
	// {
	// 	str[x] = ft_itoa(x + 1);
	// 	if (pthread_create(&g_data->phil[x], NULL, ft_routine, (void *)str[x]) != 0)
	// 		ft_exit("Error: a philo didn't seat", g_data);
	// 	x++;
	// }
	// x = 0;
	// while (x < g_data->phils_n)
	// {
	//  	if (pthread_join(g_data->phil[x], (void **)&str[x]) != 0)
	// 		printf("\tp_j:error\n");
	// 	x++;
	// }
	// x = 0;
	// while (x < g_data->phils_n)
	// {
	// 	free(str[x]);
	// 	x++;
	// }
	// free(str);
	// if (pthread_join(g_data.phil[ft_prec_phil(actual)], NULL) != 0)
	// 	printf("\tp_j:error\n");

	// if (pthread_mutex_init(g_data->mut, NULL) != 0)
	// 	ft_exit("mutex_init_fault", g_data);
	// while (g_data->x != 666)
	// {
	// 	if (pthread_create(&g_data->phil[g_data->x], NULL, ft_routine, /*(void *)&g_data->x*/NULL) != 0)
	// 		printf("\tp_c:error\n");
	// 	if (pthread_join(g_data->phil[0], /*(void **)&g_data->x*/NULL) != 0)
	// 		printf("\tp_j:error\n");
	// 	else
	// 		ft_next();
	// 	if (pthread_join(g_data->phil[1], /*(void **)&g_data->x*/NULL) != 0)
	// 		printf("\tp_j:error\n");
	// 	printf("END:-%d-\n", g_data->x);
	// }
	// if (pthread_mutex_destroy(g_data->mut) != 0)
	// 	ft_exit("mutex_free_fault", g_data);

}
