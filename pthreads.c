/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/06 16:20:38 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_pthread(void *data);
static void	*ft_memcpy(void *dst, const void *src, size_t n);

void	ft_create_thread(t_data *data)
{
	pthread_t	*philo;
	t_data		**thread_data;
	int			i;

	philo = malloc (sizeof (pthread_t) * data->philo_nb);
	if (!philo)
		return ;
	data->fork = malloc (sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return ;
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	thread_data = malloc (sizeof(t_data *) * data->philo_nb);
	while (++i < data->philo_nb)
	{
		thread_data[i] = malloc (sizeof (t_data));
		ft_memcpy(thread_data[i], data, sizeof(t_data));
		thread_data[i]->philo_nb = i + 1;
		pthread_create(&philo[i], NULL, ft_pthread, thread_data[i]);
	}
	i = -1;
	while (++i < data->philo_nb)
		pthread_join(philo[i], NULL);
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->fork[i]);
	free (philo);
	free (data->fork);
	i = -1;
	while (++i < data->philo_nb)
		free(thread_data[i]);
	free(thread_data);
}

static void	*ft_pthread(void *data)
{
	t_data	*ph;
	int		i;

	ph = (t_data *) data;
	printf("Creado el hilo %d\n", ph->philo_nb);
	i = ph->philo_nb;
	if (pthread_mutex_trylock(&ph->fork[i - 1]) == 0)
	{
		ft_print(ph, i, "has taken a fork");
		if (pthread_mutex_trylock(&ph->fork[i]) == 0)
		{
			ft_print(ph, i, "has taken a fork");
			ft_print(ph, i, "is eating");
		}
		else
			pthread_mutex_unlock(&ph->fork[i - 1]);
	}
	return (data);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
