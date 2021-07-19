/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:14:23 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/19 09:57:54 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_timestamp(long flag, t_data *data, t_philo *actual, char *str)
{
	long				x;
	long				pow;
	// long				tmp;
	struct timeval	ms;

	gettimeofday(&ms, NULL);
	pow = 1000000;
	// tmp = (ms.tv_sec % 1000) * 1000000 + ms.tv_usec;
	x = (ms.tv_sec % 1000) * pow + ms.tv_usec;
	ft_write_num((x - data->start) / pow);
	ft_write(1, ",");
	x = ms.tv_usec + pow  - (data->start % pow);
	if (x / pow != 0)
		x = x % pow;
	pow /= 10;
	while (x / pow == 0)
	{
		ft_write_num(0);
		pow /= 10;
	}
	ft_write_num((x));// / 100));
	ft_write(1, " ");
	if (!actual)
	{
		ft_write(1, " died --+++\n");//ft_write_num(0);
		return ;
	}
	else
		ft_write_num(actual->name);
	if ((/*tmp*/x / 1000) - (actual->last_eat / 1000) > data->die_t / 1000)
	{
		ft_write(1, " \t\t\tdied +++\n");
		actual->die = 666;
	}
	else
		ft_write(1, str);
	// prlongf("%d  - %d =\t", tmp, actual->last_eat);
	// prlongf("%d  - %d =\t", tmp / 1000, actual->last_eat/1000);
	// prlongf("%d  >= %d\t", tmp - actual->last_eat, data->die_t/1000);
	// prlongf("%d  >= %d\n", tmp /1000 - actual->last_eat/1000, data->die_t/1000);

	if (flag == 1)
		actual->last_eat = x;//tmp;
}

// void	*ft_dying(void *arg)
// {
// 	long				*actual;
// 	long				x;
// 	// struct timeval	ms;

// 	x = 0;
// 	actual = (long *)arg;
// 	// while (data.fork[data.x] <= 0)
// 	while (data.die[data.x] < 1)
// 		x++;//continue ;
// 	while (data.x != 666 && data.eat_n[*actual] != 0)
// 	{
// 		if (data.die[*actual] % 2 && data.die[*actual] != -1)
// 		{
// 			x = data.die[*actual];
// 			usleep(data.die_t);// - data.sleep_t);
// 			if (data.die[*actual] == x && data.x != 666 && data.eat_n[*actual] != 0)// && !gettimeofday(&ms, NULL))
// 			{
// 				pthread_mutex_lock(data.mut);
// 				data.x = 666;
// 				data.eat_n[*actual] = 0;
// 				ft_timestamp(/*ms,*/ actual);
// 				ft_write(1, " died +++\n");
// 				pthread_mutex_unlock(data.mut);
// 				return (NULL);
// 			}	
// 		}
// 	}
// 	return (NULL);
// }

void	ft_mut_fork(long status, t_philo	*actual)
{
	if (status)
	{
		pthread_mutex_lock(actual->fork_l);
		pthread_mutex_lock(actual->fork_r);
	}
	else
	{
		pthread_mutex_unlock(actual->fork_r);
		pthread_mutex_unlock(actual->fork_l);
	}
}

void	ft_sleep(t_philo	*actual)
{

	usleep(actual->data->sleep_t);
	ft_mut_fork(1, actual);
	pthread_mutex_lock(&actual->data->mut_die);
	if (*actual->f_l_stat == 0 && *actual->f_r_stat == 0 && actual->eat_n != 0 && actual->die == 666)
	{
		pthread_mutex_unlock(&actual->data->mut_die);
		return (ft_mut_fork(0, actual));
	}
	ft_timestamp(0, actual->data, actual, " is thinking\n");
	// ft_write(1, " is thinking\n");
	pthread_mutex_unlock(&actual->data->mut_die);
	ft_mut_fork(0, actual);
}

void	ft_eat(t_philo	*actual)
{
	ft_mut_fork(1, actual);
	pthread_mutex_lock(&actual->data->mut_die);
	if (*actual->f_l_stat != 0 && *actual->f_r_stat != 0)// && actual->die == 666)
	{
		pthread_mutex_unlock(&actual->data->mut_die);
		return (ft_mut_fork(0, actual));
	}
	if (*actual->f_l_stat == 1)
		ft_write(1, "\t\tstealing fork...\n");
	*actual->f_l_stat = 1;
	ft_timestamp(0, actual->data, actual, " has taken a fork\n");
	// ft_write(1, " has taken a fork\n");
	if (*actual->f_r_stat == 1)
		ft_write(1, "\t\tstealing fork...\n");
	*actual->f_r_stat = 1;
	ft_timestamp(0, actual->data, actual, " has taken a fork\n");
	// ft_write(1, " has taken a fork\n");
	ft_timestamp(1, actual->data, actual, " is eating\n");
	// ft_write(1, " is eating\n");
	actual->eat_n--;
	pthread_mutex_unlock(&actual->data->mut_die);
	usleep(actual->data->eat_t);
	pthread_mutex_lock(&actual->data->mut_die);
	// actual->eat_n--;
	// if (actual->die == 666)
	// {
		// pthread_mutex_unlock(&actual->data->mut_die);
		// return (ft_mut_fork(0, actual));
	// }
	ft_timestamp(0, actual->data, actual," is sleeping\n");
	// ft_write(1, " is sleeping\n");
	*actual->f_l_stat = 0;
	*actual->f_r_stat = 0;
	pthread_mutex_unlock(&actual->data->mut_die);
	ft_mut_fork(0, actual);

	usleep(actual->data->sleep_t);
	ft_mut_fork(1, actual);
	pthread_mutex_lock(&actual->data->mut_die);
	// if (*actual->f_l_stat == 0 && *actual->f_r_stat == 0 && actual->eat_n != 0 )//&& actual->die == 666)
	// {
	// 	pthread_mutex_unlock(&actual->data->mut_die);
	// 	return (ft_mut_fork(0, actual));
	// }
	if (actual->die == 666)
	{
		pthread_mutex_unlock(&actual->data->mut_die);
		return (ft_mut_fork(0, actual));
	}

	ft_timestamp(0, actual->data, actual, " is thinking\n");
	// ft_write(1, " is thinking\n");
	pthread_mutex_unlock(&actual->data->mut_die);
	ft_mut_fork(0, actual);
}

void	*ft_routine(void *arg)
{
	t_philo			*actual;

	actual = (t_philo *)arg;
	if (actual->name % 2 == 0)
		usleep(actual->data->eat_t - 10);
	while (actual->eat_n != 0 && actual->die != 666)
	{
		// if (actual->die)
		// 	return (NULL);
		ft_eat(actual);
		// if (actual->die)
		// 	return (NULL);
		// ft_sleep(actual);
		// if (actual->die)
		// 	return (NULL);
	}
	actual->die = 666;
	// while (data.eat_n[*actual] != 0)
	// {
				
	// }
	return (NULL);
}

void	ft_check_dying(t_philo **philos, t_data *data)//long phils_n, long die_t)
{
	long	x;
	long die;
	long *pre_status;

	x = 0;
	die = 0;
	pre_status = (long *)malloc(sizeof(long) * data->phils_n);
	while (die != 666)
	{
		x = 0;
		while (x < data->phils_n)
		{
			pthread_mutex_lock(&data->mut_die);
			pre_status[x] = philos[x]->eat_n;
			pthread_mutex_unlock(&data->mut_die);

			x++;
		}
		usleep(data->die_t);
		x = 0;
		while (x < data->phils_n)
		{
			pthread_mutex_lock(&data->mut_die);
			if (philos[x]->eat_n == pre_status[x])
			{
				// pthread_mutex_lock(&data->mut_die);
				pre_status[x] = 0;
				while (pre_status[x] < data->phils_n)
				{
					if (philos[pre_status[x]]->eat_n != 0)
					{
						die = 999;
						break ;
					}
					pre_status[x]++;
				}
				if (die != 999)
				{
					free(pre_status);
					pthread_mutex_unlock(&data->mut_die);
					return ;
				}
				ft_timestamp(/*ms,*/ philos[x]->name, data, philos[x], " died +++\n");
				// ft_write(1, " died +++\n");
				die = 666;
				x = 0;
				while (x < data->phils_n)
				{
					philos[x]->die = 666;
					x++;
				}
				pthread_mutex_unlock(&data->mut_die);
				free(pre_status);
				return ;	
				// pthread_mutex_unlock(&data->mut_die);
				// break ;
			}
			else
			{
				pthread_mutex_unlock(&data->mut_die);
				x++;
			}
		}
	}
	// x = 0;
	// while (x < data->phils_n)
	// {
	// 	philos[x]->die = 666;
	// 	x++;
	// }
	// pthread_mutex_unlock(&data->mut_die);
	// free(pre_status);

}

void	ft_lets_die(long flag, t_philo **philos, t_data *data)
{
	long	x;

	x = 0;
	while (flag && x < data->phils_n)
	{
		// pthread_mutex_lock(&data->mut_die);
		if (philos[x]->eat_n != 0)
		{
			// pthread_mutex_lock(&data->mut_die);
			break ;
		}
		// pthread_mutex_unlock(&data->mut_die);
		x++;// = ft_next_phil(x, data->phils_n);
	}
	if (x == data->phils_n)
	{
		ft_write(1, "hanno mangiato tutti\n");
		return ;
	}
	x = 0;
	while (1)
	{
		// pthread_mutex_lock(&data->mut_die);
		if (philos[x]->die == 666)
		{
			pthread_mutex_lock(&data->mut_die);
			break ;
		}
		// pthread_mutex_unlock(&data->mut_die);
		x = ft_next_phil(x, data->phils_n);
	}
	x = 0;
	while (x < data->phils_n)
	{
		philos[x]->die = 666;
		x++;
	}
	pthread_mutex_unlock(&data->mut_die);
}

void	ft_create_philo(t_philo **philos, long *fork, pthread_mutex_t *mut_fork, t_data *data)
{
	long		x;

	x = 0;
	while (x < data->phils_n)
	{
		philos[x] = (t_philo *)malloc(sizeof(t_philo) * 1);
		philos[x]->phil = (pthread_t *)malloc(sizeof(pthread_t) * 1);
		philos[x]->name = x + 1;//ft_next_phil(x);
		philos[x]->eat_n = data->eat_n;
		philos[x]->last_eat = data->start;
		philos[x]->die = 0;
		philos[x]->f_l_stat = &fork[x];
		philos[x]->fork_l = &mut_fork[x];
		philos[x]->f_r_stat = &fork[ft_next_phil(x, data->phils_n)];
		philos[x]->fork_r = &mut_fork[ft_next_phil(x, data->phils_n)];
		philos[x]->data = data;
		if (pthread_create(philos[x]->phil, NULL, ft_routine, (void *)philos[x]) != 0)
			ft_exit("Error: a philo didn't seat\n", data);
		// if (pthread_create(&data->dying_phil[x], NULL, ft_dying, (void *)&arg[x]) != 0)
			// ft_exit("Error: a philo didn't seat\n", data);
		// if (pthread_detach(data->dying_phil[x]))
		// 	prlongf("\tp_d:error\n");
		// if (pthread_detach(*philos[x]->phil))
		// 	prlongf("\tp_d:error\n");
		x++;
	}
	ft_lets_die(1, philos, data);
	//ft_check_dying(philos, data);//data->phils_n, data->die_t);			/////////////////////
	// x = 0;
	// while (x < data->phils_n)
	// {
	//  	if (pthread_join(*philos[x]->phil, NULL) != 0)
	// 		prlongf("\tp_j:error\n");
	// 	x++;
	// }
	// free(fork);
	// x = 0;
	// while (x < data->phils_n)
	// {
	// 	free(philos[x]->phil);
	// 	free(philos[x]);
	// 	x++;
	// }
	// free(philos);
}

void	ft_join_philo(t_philo **philos, t_data *data)
{
	long	x;

	x = 0;
	while (x < data->phils_n)
	{
// 	 	if (pthread_join(data->phil[x], NULL) != 0)
		if (pthread_join(*philos[x]->phil, NULL) != 0)
			printf("\tp_j:error\n");
		x++;
	}
}

void	ft_start(t_data *data)
{
	long		x;
	long		*fork;
	t_philo	**philos;
	pthread_mutex_t	*mut_fork;

	fork = (long *)malloc(sizeof(long) * data->phils_n);
	ft_init_array(fork, 0, data->phils_n);
	philos = (t_philo **)malloc(sizeof(t_philo *) * data->phils_n);
	mut_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->phils_n));
	x = 0;
	while (x < data->phils_n)
	{
	 	pthread_mutex_init(&mut_fork[x], NULL);
		x++;
	}
	pthread_mutex_init(&data->mut_die, NULL);
	// data->fork[data->x] = -1;
	ft_create_philo(philos, fork, mut_fork, data);
	// data->fork[data->x] = 0;
	ft_join_philo(philos, data);
	ft_lets_die(1, philos, data);

	// free(args);
	x = 0;
	while (x < data->phils_n)
	{
		pthread_mutex_destroy(&mut_fork[x]);
		x++;
	}
	pthread_mutex_destroy(&data->mut_die);
	free(fork);
	x = 0;
	while (x < data->phils_n)
	{
		free(philos[x]->phil);
		free(philos[x]);
		x++;
	}
	free(philos);
	free(mut_fork);
}
