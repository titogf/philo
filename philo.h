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

typedef struct s_arg
{
	long			s_time;
	int				total_ph;
	int				die;
	int				eat;
	int				sleep;
	int				m_eat;
	pthread_mutex_t	write_mutex;
}	t_arg;

typedef struct	s_philo
{
	pthread_t		th_id;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
	t_arg			*pa;
}	t_philo;

typedef struct	s_d
{
	t_philo	*ph;
	t_arg	arg;
}	t_d;

void	ft_put_finish(char *c);
int		ft_check_argv(int ac, char **av);
int		ft_atoi(char *str);

int		ft_create_thread(t_d *d);

void	ft_print(int start_time, int nb, char *str);

#endif
