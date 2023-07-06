/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 17:59:15 by gfernand         ###   ########.fr       */
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
	while (!ph->a->stop_process)
	{
		ft_processes(ph);
		if (++ph->nb_eat == ph->a->m_eat)
		{
			sem_wait(ph->a->ph_finish);
			++ph->a->nb_finished;
			sem_post(ph->a->ph_finish);
		}
	}
	return (ph);
}

static void	ft_processes(t_philo *ph)
{
	sem_wait(ph->a->forks);
	sem_wait(ph->a->forks);
	sem_wait(ph->a->write_stats);
	ft_print_stats(ph, "has taken a fork");
	sem_post(ph->a->write_stats);
	sem_wait(ph->a->write_stats);
	ft_print_stats(ph, "has taken a fork");
	sem_post(ph->a->write_stats);
	sem_wait(ph->a->write_stats);
	ft_print_stats(ph, "is eating");
	sem_post(ph->a->write_stats);
	sem_wait(ph->a->time_to_eat);
	ph->time_eat = ft_actual_time();
	sem_post(ph->a->time_to_eat);
	ft_usleep(ph->a->eat);
	sem_post(ph->a->forks);
	sem_post(ph->a->forks);
	ft_processes_2(ph);
}

static void	ft_processes_2(t_philo *ph)
{
	sem_wait(ph->a->write_stats);
	ft_print_stats(ph, "is sleeping");
	sem_post(ph->a->write_stats);
	ft_usleep(ph->a->sleep);
	sem_wait(ph->a->write_stats);
	ft_print_stats(ph, "is thinking");
	sem_post(ph->a->write_stats);
}
