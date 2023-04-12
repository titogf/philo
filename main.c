/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/12 15:53:01 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pthread(t_arg *arg);
void	*ft_he(void *i);

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
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (ft_check_argv(av) == -1)
		return (-1);
	arg = malloc (sizeof (t_arg));
	if (!arg)
		return (-1);
	if (ft_init_struct(arg, av) == -1)
		return (-1);
	ft_pthread(arg);
	free (arg);
	return (0);
}

static int	ft_init_struct(t_arg *arg, char **av)
{
	arg->philo_nb = ft_atoi(av[1]);
	arg->time_die = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	arg->nb_must_eat = 0;
	if (av[5])
		arg->nb_must_eat = ft_atoi(av[5]);
	if (arg->philo_nb < 1 || arg->time_die < 1 || arg->time_eat < 1
		|| arg->time_sleep < 1 || arg->nb_must_eat < 0)
	{
		free (arg);
		printf("Invalid arguments\n");
		return (-1);
	}
	return (0);
}

void	ft_pthread(t_arg *arg)
{
	pthread_t	*philo;
	int			i;
	int			*i_copy;

	philo = malloc (sizeof (int) * arg->philo_nb);
	if (!philo)
		return ;
	i = -1;
	while (++i <= arg->philo_nb)
	{
		i_copy = malloc (sizeof (int));
		*i_copy = i;
		pthread_create(&philo[i], NULL, ft_he, i_copy);
	}
	printf("Filosofos %d\n", arg->philo_nb);
}

void	*ft_he(void *i)
{
	int i_new = *((int*) i);
	printf("Creado el hilo %d\n", i_new);
	return (i);
}
