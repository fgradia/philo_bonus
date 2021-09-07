/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:50 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/07 14:34:37 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	ft_strncmp(char *s1, char *s2, long len)
{
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2 && --len)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_write(long fd, char *str)
{
	long	x;

	x = 0;
	while (str && str[x])
		x++;
	write(fd, str, x);
}

long	ft_atoi(char *str)
{
	long	x;
	long	tot;

	x = 0;
	tot = 0;
	if (str && (str[x] < '0' || str[x] > '9'))
		ft_exit("Invalid args..", NULL);
	while (str && str[x] && str[x] >= '0' && str[x] <= '9')
		tot = tot * 10 + str[x++] - 48;
	if (str[x] && (str[x] < '0' || str[x] > '9'))
		ft_exit("Invalid args..", NULL);
	return (tot);
}

void	ft_write_num(long num)
{
	char	q;

	if (num / 10 != 0)
		ft_write_num(num / 10);
	q = (num % 10) + 48;
	write(1, &q, 1);
}
