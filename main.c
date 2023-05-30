/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/12 17:20:16 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_struct(t_data *data, char **av, long start_time);

/*static void	leaks(void)
{
	system("leaks philo");
}*/

int	main(int ac, char **av)
{
	t_data	*data;
	struct timeval start_time;
	long int	time;

	gettimeofday(&start_time, NULL);
	time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	//atexit(leaks);
	if (ac != 5 && ac != 6)
	{
		printf("Invalid datauments\n");
		return (0);
	}
	if (ft_check_argv(av) == -1)
		return (-1);
	data = malloc (sizeof (t_data));
	if (!data)
		return (-1);
	if (ft_init_struct(data, av, time) == -1)
		return (-1);
	ft_create_thread(data);
	free (data);
	return (0);
}

static int	ft_init_struct(t_data *data, char **av, long time)
{
	data->start_time = time;
	data->philo_nb = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->nb_must_eat = 0;
	if (av[5])
		data->nb_must_eat = ft_atoi(av[5]);
	if (data->philo_nb < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1 || data->nb_must_eat < 0)
	{
		free (data);
		printf("Invalid arguments\n");
		return (-1);
	}
	return (0);
}

void	ft_print(t_data *ph, int nb, char *str)
{
	struct timeval tv;
	long int	miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - ph->start_time ;
	printf("%ld Philo %i %s\n", miliseconds, nb, str);
	sleep(3);
	usleep(28340);
}
