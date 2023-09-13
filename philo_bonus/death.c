/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:20 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 17:18:12 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(t_philo *ph)
{
	sem_wait(ph->a->sem_death);
	if (ph->a->nb_finished == ph->a->total_ph)
	{
		ph->a->stop_process = 2;
		sem_post(ph->a->sem_death);
		return (1);
	}
	else if ((ft_actual_time() - ph->time_eat) >= ph->a->die)
	{
		sem_wait(ph->a->write_stats);
		ft_print_stats(ph, "died");
		ph->a->stop_process = 1;
		sem_post(ph->a->write_stats);
		sem_post(ph->a->sem_death);
		return (1);
	}
	sem_post(ph->a->sem_death);
	return (0);
}

void	ft_kill(t_d *d)
{
	int	i;

	i = -1;
	while (++i < d->arg.total_ph)
		kill(d->arg.pid[i], SIGKILL);
	sem_close(d->arg.sem_forks);
	sem_close(d->arg.write_stats);
	sem_close(d->arg.sem_death);
	sem_close(d->arg.ph_finish);
	sem_close(d->arg.time_to_eat);
}

void	ft_usleep(long int time)
{
	long	start;

	start = ft_actual_time();
	usleep(time * 920);
	while (ft_actual_time() < start + time)
		usleep(time * 3);
}
