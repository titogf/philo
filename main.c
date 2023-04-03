/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/03 16:46:27 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_struct(t_arg *arg, char **av);

int	main(int ac, char **av)
{
	t_arg	*arg;

	if (ac != 5)
		return (0);
	if (ft_check_argv(av) == -1)
		return (-1);
	arg = malloc (sizeof (t_arg));
	if (ft_init_struct(arg, av) == -1)
	{
		printf("Invalid arguments\n");
		free (arg);
		return (-1);
	}
	return (0);
}

static int	ft_init_struct(t_arg *arg, char **av)
{
	arg->philo_nb = ft_atoi(av[1]);
	if (arg->philo_nb < 0)
		return (-1);
	arg->time_die = ft_atoi(av[2]);
	if (arg->time_die < 0)
		return (-1);
	arg->time_eat = ft_atoi(av[3]);
	if (arg->time_eat < 0)
		return (-1);
	arg->time_sleep = ft_atoi(av[4]);
	if (arg->time_sleep < 0)
		return (-1);
	return (0);
}
