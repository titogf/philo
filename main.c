/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/03 20:08:35 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_struct(t_arg *arg, char **av);

/*static void	leaks(void)
{
	system("leaks philo");
}*/

int	main(int ac, char **av)
{
	t_arg	*arg;

//	atexit(leaks);
	if (ac != 5 && ac != 6)
		return (0);
	if (ft_check_argv(av) == -1)
		return (-1);
	arg = malloc (sizeof (t_arg));
	if (ft_init_struct(arg, av) == -1)
		return (-1);
	free (arg);
	return (0);
}

static int	ft_init_struct(t_arg *arg, char **av)
{
	arg->philo_nb = ft_atoi(av[1]);
	arg->time_die = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	if (arg->philo_nb < 1 || arg->time_die < 1
		|| arg->time_eat < 1 || arg->time_sleep < 1)
	{
		free (arg);
		printf("Invalid arguments");
		return (-1);
	}
	return (0);
}
