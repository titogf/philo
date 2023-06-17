/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/06 15:46:40 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_argv(int ac, char **av);
static void	ft_init_struct_arg(t_d *d, char **av);
static void	ft_init_struct_philo(t_d *d);

/*static void	leaks(void)
{
	system("leaks philo");
}*/

int	main(int ac, char **av)
{
	t_d	d;

//	atexit(leaks);
	if (ft_check_argv(ac, av) == -1)
		return (-1);
	ft_init_struct_arg(&d, av);
	d.ph = malloc(sizeof (t_philo) * d.arg.total_ph);
	if (!d.ph)
		ft_put_finish("Malloc error\n");
	ft_init_struct_philo(&d);
	if (!ft_create_thread(&d))
	{
		free(d.ph);
		return (0);
	}
	sleep(3);
	free(d.ph);
	return (0);
}

static int	ft_check_argv(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid arguments\n");
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
				printf("Invalid arguments\n");
				return (-1);
			}
		}
	}
	return (0);
}

static void	ft_init_struct_arg(t_d *d, char **av)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	d->arg.s_time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	d->arg.total_ph = ft_atoi(av[1]);
	d->arg.die = ft_atoi(av[2]);
	d->arg.eat = ft_atoi(av[3]);
	d->arg.sleep = ft_atoi(av[4]);
	d->arg.m_eat = -1;
	if (av[5])
	{
		d->arg.m_eat = ft_atoi(av[5]);
		if (d->arg.m_eat == -1)
			ft_put_finish("Invalid arguments\n");
	}
	if (d->arg.total_ph < 1 || d->arg.die < 1 || d->arg.eat < 1
		|| d->arg.sleep < 1 || d->arg.m_eat < 0)
		ft_put_finish("Invalid arguments\n");
}

static void	ft_init_struct_philo(t_d *d)
{
	int	i;

	pthread_mutex_init(&d->arg.write_stats, NULL);
	pthread_mutex_init(&d->arg.mutex_death, NULL);
	pthread_mutex_init(&d->arg.time_to_eat, NULL);
	d->arg.death = 0;
	i = -1;
	while (++i < d->arg.total_ph)
	{
		d->ph[i].id = i + 1;
		d->ph[i].nb_eat = 0;
		d->ph[i].time_eat = d->arg.s_time;
		d->ph[i].r_f = NULL;
		pthread_mutex_init(&d->ph[i].l_f, NULL);
		if (d->arg.total_ph == 1)
			return ;
		if (i == d->arg.total_ph - 1)
			d->ph[i].r_f = &d->ph[0].l_f;
		else
			d->ph[i].r_f = &d->ph[i + 1].l_f;
	}
}
