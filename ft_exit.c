/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:33 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/14 18:58:49 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_exit(char *str, t_data *g_data)
{
	ft_write(2, str);
	ft_write(2, "\n");
	if (g_data->eat_n)
		free(g_data->eat_n);
	if (g_data->fork)
		free(g_data->fork);
	if (g_data->fork_2)
		free(g_data->fork_2);
	if (g_data->die)
		free(g_data->die);
	if (g_data->phil)
		free(g_data->phil);
	if (g_data->dying_phil)
		free(g_data->dying_phil);
	if (g_data->mut)
		free(g_data->mut);
	// printf("check leaks\n");
	// read(0, NULL, 1);
	exit(0);
}
