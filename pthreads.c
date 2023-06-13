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

	ph = (t_philo *) data;
	printf("Creado el hilo %d\n", ph->id);
	return (ph);
}
