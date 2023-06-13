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

int	ft_create_thread(t_d *d)
{
	int	i;
	int	t;

	i = -1;
	while (++i < d->arg.total_ph)
	{
		d->ph[i].pa = &d->arg;
		t = pthread_create(&d->ph[i].th_id, NULL, ft_pthread, &d->ph[i]);
		if (t != 0)
			return (0);
	}
	return (1);
}

static void	*ft_pthread(void *data)
{
	t_philo	*ph;
	//int		i;

	ph = (t_philo *) data;
	printf("Creado el hilo %d\n", ph->pa->total_ph);
	/*i = ph->philo_nb;
	pthread_mutex_lock(&ph->fork[i - 1]);
	pthread_mutex_lock(ph->write_mutex);
	ft_print(ph, i, "has taken a fork");
	pthread_mutex_unlock(ph->write_mutex);
	pthread_mutex_lock(&ph->fork[i];
	pthread_mutex_lock(ph->write_mutex);
	ft_print(ph, i, "has taken a fork");
	pthread_mutex_unlock(ph->write_mutex);
	pthread_mutex_lock(write_mutex);
	ft_print(ph, i, "is eating");
	pthread_mutex_unlock(ph->write_mutex);
	pthread_mutex_unlock(&ph->fork[i - 1]);
	pthread_mutex_unlock(&ph->fork[i]);*/
	return (ph);
}
