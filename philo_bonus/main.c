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

#include "philo.h"

static int	ft_check_argv(int ac, char **av);
static void	ft_init_struct_arg(t_d *d, char **av);
static void	ft_init_struct_philo(t_d *d);
static void	ft_death(t_philo *ph);

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
	if (!ft_create_process(&d))
	{
		free(d.ph);
		return (0);
	}
	ft_death(d.ph);
	ft_kill(&d);
	free(d.ph);
	return (0);
}

static int	ft_check_argv(int ac, char **av)
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
				printf("Invalid arguments, only numbers are expected\n");
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
		if (d->arg.m_eat < 1)
			ft_put_finish("Invalid arguments, positive values are expected\n");
	}
	if (d->arg.total_ph < 1 || d->arg.die < 1 || d->arg.eat < 1
		|| d->arg.sleep < 1)
		ft_put_finish("Invalid arguments, positive values are expected\n");
}

static void	ft_init_struct_philo(t_d *d)
{
	int	i;

	sem_unlink("sem_forks");
	sem_unlink("write_stats");
	sem_unlink("sem_death");
	sem_unlink("time_to_eat");
	sem_unlink("ph_finish");
	d->arg.sem_forks = sem_open("sem_forks", O_CREAT, S_IRWXU, d->arg.total_ph);
	d->arg.write_stats = sem_open("write_stats", O_CREAT, S_IRWXU, 1);
	d->arg.sem_death = sem_open("sem_death", O_CREAT, S_IRWXU, 1);
	d->arg.time_to_eat = sem_open("time_to_eat", O_CREAT, S_IRWXU, 1);
	d->arg.ph_finish = sem_open("ph_finish", O_CREAT, S_IRWXU, 1);
	d->arg.stop_process = 0;
	d->arg.nb_finished = 0;
	i = -1;
	while (++i < d->arg.total_ph)
	{
		d->ph[i].id = i + 1;
		d->ph[i].nb_eat = 0;
		d->ph[i].time_eat = d->arg.s_time;
		if (d->arg.total_ph == 1)
			return ;
	}
}

static void	ft_death(t_philo *ph)
{
	int	i;
	int	b;

	b = 0;
	while (!b)
	{
		i = 0;
		while (i < ph->a->total_ph && !ft_check(ph))
			++i;
		if (ph->a->stop_process)
			b = -1;
	}
	if (ph->a->stop_process == 2)
		printf("Each philosophers ate %d times\n", ph->a->m_eat);
}
