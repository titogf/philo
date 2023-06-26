
#include "philo.h"

static int	ft_check_argv(int ac, char **av);
static void	ft_init_struct_arg(t_d *d, char **av);
//static void	ft_death(t_philo *ph);

/*static void	leaks(void)
{
	system("leaks philo");
}*/
/*void	ft_usleep(long int time)
{
	long	start;

	start = ft_actual_time();
	usleep(time * 920);
	while (ft_actual_time() < start + time)
		usleep(time * 3);
}*/
int	main(int ac, char **av)
{
	t_d	d;

//	atexit(leaks);
	if (ft_check_argv(ac, av) == -1)
		return (-1);
	ft_init_struct_arg(&d, av);
	ft_init_struct_philo(&d);
	//ft_death(d.ph);
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

/*static void	ft_death(t_philo *ph)
{
	int	i;
	int	b;

	b = 0;
	while (!b)
	{
		i = 0;
		while (i < ph->a->total_ph && !ft_check(&ph[i]))
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
}*/
