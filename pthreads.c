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
long int	actual_time(void);

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
	if (ph->id % 2 == 0)
		usleep(ph->pa->eat / 10);
	ft_print_stats(ph->pa->s_time, ph->id, "prueba");
	return (ph);
}

static void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time)
		usleep(time / 10);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		tv;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
