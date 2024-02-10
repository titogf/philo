/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 18:27:19 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_argv(int ac, char **av);
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

static int	check_argv(int ac, char **av)
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

static void	death(t_philo *ph)
{
	int	i;
	int	b;

	b = 0;
	while (!b)
	{
		i = 0;
		while (i < ph->a->total_ph && !check(&ph[i]))
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
