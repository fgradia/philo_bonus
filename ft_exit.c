/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:33 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 09:52:25 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_exit(char *str, t_data *data)
{
	ft_write(2, str);
	ft_write(2, "\n");
	// if (data->eat_n)
	// 	free(data->eat_n);
	// if (data->fork)
	// 	free(data->fork);
	// if (data->fork_2)
	// 	free(data->fork_2);
	// if (data->die)
	// 	free(data->die);
	// if (data->phil)
	// 	free(data->phil);
	// if (data->dying_phil)
	// 	free(data->dying_phil);
	// if (data->mut_fork)
	// 	free(data->mut_fork);
	// printf("check leaks\n");
	// read(0, NULL, 1);
	exit(0);

	(void)data;
}
