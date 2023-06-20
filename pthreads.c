/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 14:11:06 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_pthread(void *data);
static void	ft_processes(t_philo *ph);
static void	ft_processes_2(t_philo *ph);

int	ft_create_thread(t_d *d)
{
	int	i;
	int	t;

	i = -1;
	while (++i < d->arg.total_ph)
	{
		d->ph[i].a = &d->arg;
		t = pthread_create(&d->ph[i].th_id, NULL, ft_pthread, &d->ph[i]);
		if (t != 0)
		{
			printf("Pthread error\n");
			return (0);
		}
	}
	return (1);
}

static void	*ft_pthread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *) data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->a->die / 8);
	while (!ph->a->stop_process)
	{
		ft_processes(ph);
		if (++ph->nb_eat == ph->a->m_eat)
		{
			pthread_mutex_lock(&ph->a->ph_finish);
			++ph->a->nb_finished;
			pthread_mutex_unlock(&ph->a->ph_finish);
		}
	}
	return (ph);
}

static void	ft_processes(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->a->write_stats);
	if (!ph->r_f)
		return ;
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->a->write_stats);
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "is eating");
	pthread_mutex_unlock(&ph->a->write_stats);
	pthread_mutex_lock(&ph->a->time_to_eat);
	ph->time_eat = ft_actual_time();
	pthread_mutex_unlock(&ph->a->time_to_eat);
	ft_usleep(ph->a->eat);
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
	ft_processes_2(ph);
}

static void	ft_processes_2(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "is sleeping");
	pthread_mutex_unlock(&ph->a->write_stats);
	ft_usleep(ph->a->sleep);
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "is thinking");
	pthread_mutex_unlock(&ph->a->write_stats);
}
