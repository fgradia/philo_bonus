#include "philolib.h"

void	ft_exit(char *str, t_data *g_data)
{
	ft_write(2, str);
	if (g_data->phil)
		free(g_data->phil);
	if (g_data->mut)
		free(g_data->mut);
	printf("check leaks\n");
	read(0, NULL, 1);
}
