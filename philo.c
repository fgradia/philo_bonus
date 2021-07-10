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

void	ft_init_data(char **av, t_data *g_data)
{
	g_data->phils_n = ft_atoi(av[1]);
	g_data->die_t = ft_atoi(av[2]);
	g_data->eat_t = ft_atoi(av[3]);
	g_data->sleep_t = ft_atoi(av[4]);
	g_data->eat_n = -1;
	g_data->x = 0;
	g_data->phil = (pthread_t *)malloc(sizeof(pthread_t) * g_data->phils_n);
	g_data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!g_data->phil || !g_data->mut)
		ft_exit("malloc_fault", g_data);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		ft_init_data(av, &g_data);
		if (ac == 6)
			g_data.eat_n = ft_atoi(av[5]) * g_data.phils_n;
		ft_start(&g_data);
	}
	else
		exit(2);
	ft_exit("", &g_data);
}
