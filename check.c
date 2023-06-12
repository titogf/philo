/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:39:02 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/03 14:04:28 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_max_int(char *str, int i, int nb);

int	ft_check_argv(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid arguments\n");
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
				printf("Invalid arguments\n");
				return (-1);
			}
		}
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	if (!str || !str[0])
		return (-1);
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - 48);
		if (ft_max_int(str, i, nb) == -1)
			return (-1);
		i++;
	}
	return (nb);
}

static int	ft_max_int(char *str, int i, int nb)
{
	int	m;

	if (nb > 214748364)
	{
		if (str[i + 1])
			return (-1);
	}
	if (nb == 214748364 && str[i + 1])
	{
		if (str[i + 2])
			return (-1);
		m = (str[++i] - 48);
		if (m > 8)
			return (-1);
		nb = nb * 10 + (str[i] - 48);
	}
	return (0);
}
