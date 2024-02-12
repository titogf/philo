/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2024/02/12 16:12:52 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	death(t_philo *ph);

int	main(int ac, char **av)
{
	t_d	d;

	if (check_argv(ac, av) == -1)
		return (-1);
	if (init_struct_arg(&d, av) == -1)
		return (-1);
	d.ph = malloc(sizeof (t_philo) * d.arg.total_ph);
	if (!d.ph)
		return (put_finish("Malloc error\n"));
	init_struct_philo(&d);
	if (!create_thread(&d))
	{
		free(d.ph);
		return (0);
	}
	death(d.ph);
	free(d.ph);
	return (0);
}

static void	death(t_philo *ph)
{
	int	i;
	int	b;

	b = 0;
	while (!b)
	{
		i = 0;
		while (i < ph->a->total_ph && !check_death(&ph[i]))
			++i;
		if (ph->a->stop_process)
			b = -1;
	}
	while (++i < ph->a->total_ph)
		pthread_join(ph[i].th_id, NULL);
	i = -1;
	while (++i < ph->a->total_ph)
		pthread_mutex_destroy(&ph[i].l_f);
	pthread_mutex_destroy(&ph->a->write_stats);
	pthread_mutex_destroy(&ph->a->mutex_death);
	pthread_mutex_destroy(&ph->a->ph_finish);
	if (ph->a->stop_process == 2)
		printf("Each philosophers ate %d times\n", ph->a->m_eat);
}
