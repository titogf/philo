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

#include "../philo.h"

int	check_argv(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid, five or six arguments are expected\n");
		return (-1);
	}
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Invalid arguments, positive numbers are expected\n");
				return (-1);
			}
		}
	}
	return (0);
}

int	check_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->mutex_death);
	if (ph->a->nb_finished == ph->a->total_ph)
	{
		ph->a->stop_process = 2;
		pthread_mutex_unlock(&ph->a->mutex_death);
		return (1);
	}
	else if ((actual_time() - ph->time_eat) >= ph->a->die)
	{
		pthread_mutex_lock(&ph->a->write_stats);
		print_stats(ph, "died");
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
	long	start;

	start = actual_time();
	usleep(time * 920);
	while (actual_time() < start + time)
		usleep(time * 3);
}
