/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:50 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 09:56:42 by fgradia          ###   ########.fr       */
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

long	ft_strlen(char *str)
{
	long	x;

	x = 0;
	while (str && str[x])
		x++;
	return (x);
}

void	ft_write(long fd, char *str)
{
	write(fd, str, ft_strlen(str));
	// write(fd, "\n", 1);
}

long	ft_atoi(char *str)
{
	long	x;
	long	tot;

	x = 0;
	tot = 0;
	while (str && str[x] && str[x] >= '0' && str[x] <= '9')
		tot = tot * 10 + str[x++] - 48;
	return (tot);
}

char	*ft_itoa(long num)
{
	long		x;
	long		tmp;
	char	*new;

	x = 1;
	tmp = num;
	while (tmp >= 10 && ++x)
		tmp /= 10;
	new = (char *)malloc(sizeof(char) * (x + 1));
	new[x] = '\0';
	while (x != 0)
	{
		new[--x] = num % 10 + 48;
		num /= 10;
	}
	return (new);
}

void	ft_write_num(long num)
{
	char	q;

	if (num / 10 != 0)
		ft_write_num(num / 10);
	q = (num % 10) + 48;
	write(1, &q, 1);
}
