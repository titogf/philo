/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/06 16:20:38 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_pthread(void *data);
static void	ft_usleep(long int time_in_ms);
static void	ft_processes(t_philo *ph);
static void	ft_processes_2(t_philo *ph);
static void	ft_check(t_philo *ph);

static void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = ft_actual_time();
	while ((ft_actual_time() - start_time) < time)
		usleep(time / 10);
}

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
		ft_usleep(ph->a->eat / 10);
	while (!ph->a->stop_process)
	{
		ft_check(ph);
		if (!ph->a->stop_process)
		{
			ft_processes(ph);
			if (++ph->nb_eat == ph->a->m_eat)
			{
				pthread_mutex_lock(&ph->a->ph_finish);
				++ph->a->nb_finished;
				pthread_mutex_unlock(&ph->a->ph_finish);
				
			}
		}
	}
	return (ph);
}

static void	ft_check(t_philo *ph)
{
	if (ph->a->nb_finished == ph->a->total_ph)
		ph->a->stop_process = 2;
	if ((ph->time_eat - ft_actual_time()) >= ph->a->die)
		ph->a->stop_process = 1;
}

static void	ft_processes(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->a->write_stats);
	ft_print_stats(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->a->write_stats);
	if (!ph->r_f)
	{
		pthread_mutex_lock(&ph->a->mutex_death);
		ph->a->stop_process = 1;
		pthread_mutex_unlock(&ph->a->mutex_death);
		return ;
	}
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
