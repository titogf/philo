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

static void	ft_init_struct(t_d *d, char **av);

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
	ft_init_struct(&d, av);
	d.ph = malloc(sizeof (t_philo) * d.arg.total_ph);
	if (!d.ph)
		ft_put_finish("Malloc error\n");
	if (!ft_create_thread(&d))
		ft_put_finish("Pthread error\n");
	sleep(3);
	free(d.ph);
	return (0);
}

static void	ft_init_struct(t_d *d, char **av)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	d->arg.s_time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	d->arg.total_ph = ft_atoi(av[1]);
	d->arg.die = ft_atoi(av[2]);
	d->arg.eat = ft_atoi(av[3]);
	d->arg.sleep = ft_atoi(av[4]);
	d->arg.m_eat = 0;
	if (av[5])
		d->arg.m_eat = ft_atoi(av[5]);
	if (d->arg.total_ph < 1 || d->arg.die < 1 || d->arg.eat < 1
		|| d->arg.sleep < 1 || d->arg.m_eat < 0)
		ft_put_finish("Invalid arguments\n");
}

void	ft_print(int start_time, int nb, char *str)
{
	struct timeval	tv;
	long int		miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time ;
	printf("%ld Philo %i %s\n", miliseconds, nb, str);
	sleep(3);
	usleep(28340);
}

void	ft_put_finish(char *c)
{
	int	i;

	i = -1;
	while (c[++i])
		write(1, &c[i], 1);
	exit (1);
}
