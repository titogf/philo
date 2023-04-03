/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/03 13:59:34 by gfernand         ###   ########.fr       */
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
	arg->philosophers = ft_atoi(av[1]);
	if (arg->philosophers < 0)
		return (-1);
	arg->die_time = ft_atoi(av[2]);
	if (arg->die_time < 0)
		return (-1);
	arg->eat_time = ft_atoi(av[3]);
	if (arg->eat_time < 0)
		return (-1);
	arg->sleep_time = ft_atoi(av[4]);
	if (arg->sleep_time < 0)
		return (-1);
	return (0);
}
