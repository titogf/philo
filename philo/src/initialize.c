#include "../philo.h"

int	init_struct_arg(t_d *d, char **av)
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
		{
			put_finish("Invalid arguments, positive values are expected\n");
			return (-1);
		}
	}
	if (d->arg.total_ph < 1 || d->arg.die < 1 || d->arg.eat < 1
		|| d->arg.sleep < 1)
	{
		put_finish("Invalid arguments, positive values are expected\n");
		return (-1);
	}
	return (0);
}

void	init_struct_philo(t_d *d)
{
	int	i;

	pthread_mutex_init(&d->arg.write_stats, NULL);
	pthread_mutex_init(&d->arg.mutex_death, NULL);
	pthread_mutex_init(&d->arg.time_to_eat, NULL);
	pthread_mutex_init(&d->arg.ph_finish, NULL);
	d->arg.stop_process = 0;
	d->arg.nb_finished = 0;
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
