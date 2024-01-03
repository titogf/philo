/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:24:46 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 11:24:48 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_max_int(char *str, int i, int nb);

void	ft_print_stats(t_philo *ph, char *str)
{
	long int		miliseconds;

	miliseconds = ft_actual_time() - ph->a->s_time;
	if (!ph->a->stop_process)
		printf("%ld Philo %i %s\n", miliseconds, ph->id, str);
}

long	ft_actual_time(void)
{
	long				time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_put_finish(char *c)
{
	int	i;

	i = -1;
	while (c[++i])
		write(1, &c[i], 1);
	return (-1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	if (!str || !str[0])
		return (-1);
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - 48);
		if (ft_max_int(str, i, nb) == -1)
			return (-1);
		i++;
	}
	return (nb);
}

static int	ft_max_int(char *str, int i, int nb)
{
	int	m;

	if (nb > 214748364)
	{
		if (str[i + 1])
			return (-1);
	}
	if (nb == 214748364 && str[i + 1])
	{
		if (str[i + 2])
			return (-1);
		m = (str[++i] - 48);
		if (m > 8)
			return (-1);
		nb = nb * 10 + (str[i] - 48);
	}
	return (0);
}
