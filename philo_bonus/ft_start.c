/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/09/15 16:13:34 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_eat_sleep_think(t_philo *actual, sem_t *semaphore)
{
	if (ft_thinking222(actual, semaphore))
		return ;
	if (ft_timestamp(-1, actual->data, actual, "\033[0;32m is eating\033[0m\n"))
		return ;
	if (ft_usleep(-1, actual, actual->data))
		return ;
	actual->eat_n--;
	sem_post(semaphore);
	sem_post(semaphore);
	if (ft_timestamp(-2, actual->data, actual, " is sleeping\n"))
		return ;
	if (ft_usleep(-2, actual, actual->data))
		return ;
}

void	ft_routine(t_philo	*philos, int actual)
{
	philos[actual].semaphore = sem_open("forks", O_RDWR);
	philos[actual].die_sem = sem_open("die", O_RDWR);
	if (philos[actual].semaphore == SEM_FAILED
		|| philos[actual].die_sem == SEM_FAILED)
	{
		free(philos);
		ft_exit("sem_open failed child\n", philos[actual].data);
	}
	while (philos[actual].eat_n != 0 && philos[actual].data->die_all != 666)
		ft_eat_sleep_think(&philos[actual], philos[actual].semaphore);
	if (sem_close(philos[actual].semaphore) < 0
		|| sem_close(philos[actual].die_sem) < 0)
	{
		free(philos);
		ft_exit("sem_close failed child\n", philos[actual].data);
	}
	free(philos);
	exit(0);
}

void	ft_check_piddio(t_philo *philos, t_data *data)
{
	int	*ret;
	int	x;
	int	first;
	int	first_status;

	first = waitpid(-1, &first_status, 0);
	first = ft_find_phid(philos, first);
	ret = (int *)malloc(sizeof(int) * data->phils_n);
	ret[first] = first_status;
	x = 0;
	if (first_status == 0)
		ft_check_eat(philos, data, first, ret);
	else
		ft_kill(philos, first, data);
	while (x < data->phils_n && ret[x] == 0)
		x++;
	if (x == data->phils_n)
		ft_write(1, "\033[0;36mphilos are full!\033[0m\n");
	free(philos);
	free(ret);
	if (sem_unlink("forks") < 0 || sem_unlink("die") < 0)
		ft_exit("sem_unlink failed\n", data);
	printf("\033[2;34munlinked sem\033[0m\n");
}

void	ft_create_philo(t_philo *philos, t_data *data, int x)
{
	while (x < data->phils_n)
	{
		philos[x].name = x + 1;
		philos[x].eat_n = data->eat_n;
		philos[x].last_eat = data->start;
		philos[x].last_sleep = data->start;
		philos[x].data = data;
		philos[x].data->tofree = philos;
		philos[x].phid = fork();
		if (philos[x].phid < 0)
		{
			free(philos);
			ft_exit("Philo failed to seat\n", data);
		}
		else if (philos[x].phid == 0)
		{
			if (data->phils_n == 1)
				ft_alone(&philos[x]);
			else
				ft_routine(philos, x);
		}
		x++;
	}
}

void	ft_start(t_data *data)
{
	t_philo	*philos;
	sem_t	*semaphore;
	sem_t	*die_sem;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->phils_n);
	semaphore = sem_open("forks", O_CREAT | O_EXCL, 0777, data->phils_n);
	die_sem = sem_open("die", O_CREAT | O_EXCL, 0777, 1);
	if (semaphore == SEM_FAILED || die_sem == SEM_FAILED)
	{
		free(philos);
		ft_exit("sem_open failed parent\n", data);
	}
	if (sem_close(semaphore) < 0 || sem_close(die_sem) < 0)
		ft_exit("sem_close failed\n", data);
	ft_create_philo(philos, data, 0);
	ft_check_piddio(philos, data);
}
