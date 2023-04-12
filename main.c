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

void	ft_pthread(t_data *data);
void	*ft_he(void *data);

static int	ft_init_struct(t_data *data, char **av);

/*static void	leaks(void)
{
	system("leaks philo");
}*/

int	main(int ac, char **av)
{
	t_data	*data;

//	atexit(leaks);
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
	if (ft_init_struct(data, av) == -1)
		return (-1);
	ft_create_thread(data);
	free (data);
	return (0);
}

static int	ft_init_struct(t_data *data, char **av)
{
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
