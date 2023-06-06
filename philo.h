/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:54 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/06 14:03:41 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long			s_time;
	int				philo_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	pthread_mutex_t	*fork;
}	t_data;

int		ft_check_argv(char **av);
int		ft_atoi(char *str);

void	ft_create_thread(t_data *data);

void	ft_print(t_data *ph, int nb, char *str);

#endif
