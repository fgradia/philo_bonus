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

void	*ft_routine(void *arg)
{
	char	*actual;

	actual = ft_itoa(g_data.x + 1);
	printf("seated phil: %s\n", (char *)arg);
	// printf("%d\t%d\n", ft_strncmp(actual, (char *)arg, ft_strlen(actual)), ft_strncmp(actual, (char *)arg, ft_strlen((char *)arg)));
	if (!ft_strncmp(actual, (char *)arg, ft_strlen(actual)) && !ft_strncmp(actual, (char *)arg, ft_strlen((char *)arg) + 1))
		printf("\t\teating phil: %s\n", (char *)arg);
	else
		usleep(g_data.sleep_t);
	free(actual);
	return (arg);
}

void	ft_create_philo(char **str, t_data *g_data)
{
	int	x;

	x = 0;
	while (x < g_data->phils_n)
	{
		str[x] = ft_itoa(x + 1);
		if (pthread_create(&g_data->phil[x], NULL, ft_routine, (void *)str[x]) != 0)
			ft_exit("Error: a philo didn't seat", g_data);
		x++;
	}
}

void	ft_join_philo(char **str, t_data *g_data)
{
	int	x;

	x = 0;
	while (x < g_data->phils_n)
	{
	 	if (pthread_join(g_data->phil[x], (void **)&str[x]) != 0)
			printf("\tp_j:error\n");
		x++;
	}
}

void	ft_start(t_data *g_data)
{
	char	**str;
	// int		x;
	pthread_mutex_init(g_data->mut, NULL);
	str = (char **)malloc(sizeof(char *) * (g_data->phils_n + 1));
	str[g_data->phils_n] = NULL;
	ft_create_philo(str, g_data);
	ft_join_philo(str, g_data);
	ft_free_matr(str);
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
