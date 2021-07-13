/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:50 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/13 19:16:23 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_strncmp(char *s1, char *s2, int len)
{
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2 && --len)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str && str[x])
		x++;
	return (x);
}

void	ft_write(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	ft_atoi(char *str)
{
	int	x;
	int	tot;

	x = 0;
	tot = 0;
	while (str && str[x] && str[x] >= '0' && str[x] <= '9')
		tot = tot * 10 + str[x++] - 48;
	return (tot);
}

char	*ft_itoa(int num)
{
	int		x;
	int		tmp;
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
