/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/04/12 17:20:18 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_pthread(void *data);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	ft_create_thread(t_data *data)
{
	pthread_t	*philo;
	t_data		*thread_data;
	pthread_mutex_t	*fork;
	int			i;

	philo = malloc (sizeof (int) * data->philo_nb);
	if (!philo)
		return ;
	fork = NULL;
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&fork[i], NULL);
	i = -1;
	while (++i < data->philo_nb)
	{
		thread_data = malloc (sizeof (t_data));
		ft_memcpy(thread_data, data, sizeof(t_data));
		thread_data->philo_nb = i + 1;
		pthread_create(&philo[i], NULL, ft_pthread, thread_data);
	}
	free (philo);
}

static void	*ft_pthread(void *data)
{
	t_data	*ph;

	ph = (t_data *) data;
	printf("Creado el hilo %d\n", ph->philo_nb);
	return (data);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
