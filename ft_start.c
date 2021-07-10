#include "philolib.h"

void	*ft_routine(void *arg)
{
	char	*actual;

	actual = ft_itoa(g_data.x + 1);
	printf("seated phil: %s\n", (char *)arg);
	printf("%d\t%d\n", ft_strncmp(actual, (char *)arg, ft_strlen(actual)), ft_strncmp(actual, (char *)arg, ft_strlen((char *)arg)));
	if (!ft_strncmp(actual, (char *)arg, ft_strlen((char *)arg)) && !ft_strncmp(actual, (char *)arg, ft_strlen((char *)arg) + 1))
		printf("\t\teating phil: \n");
	else
		usleep(g_data.sleep_t);
	free(actual);
	return (NULL);
}

void	ft_start(t_data *g_data)
{
	char	*str;
	int		x;

	x = 0;
	while (x < g_data->phils_n)
	{
		str = ft_itoa(x + 1);
		if (pthread_create(&g_data->phil[x], NULL, ft_routine, (void *)str) != 0)
			ft_exit("Error: a philo didn't seat", g_data);
		free(str);
		x++;
	}
	// if (pthread_join(g_data.phil[ft_next_phil(actual)], NULL) != 0)
	// 	printf("\tp_j:error\n");
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
