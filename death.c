/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:20 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 14:11:26 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->mutex_death);
	if (ph->a->nb_finished == ph->a->total_ph)
	{
		ph->a->stop_process = 2;
		pthread_mutex_unlock(&ph->a->mutex_death);
		return (1);
	}
	else if ((ft_actual_time() - ph->time_eat) >= ph->a->die)
	{
		pthread_mutex_lock(&ph->a->write_stats);
		ft_print_stats(ph, "died");
		ph->a->stop_process = 1;
		pthread_mutex_unlock(&ph->a->write_stats);
		pthread_mutex_unlock(&ph->a->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&ph->a->mutex_death);
	return (0);
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = ft_actual_time();
	while ((ft_actual_time() - start_time) < time)
		usleep(time / 10);
}
