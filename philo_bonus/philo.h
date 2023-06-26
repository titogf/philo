/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:36:54 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 14:11:35 by gfernand         ###   ########.fr       */
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
}	t_arg;

typedef struct s_d
{
	t_arg	arg;
}	t_d;

void	ft_print_stats(t_philo *ph, char *str);
void	ft_put_finish(char *c);
int		ft_atoi(char *str);

int		ft_create_thread(t_d *d);

long	ft_actual_time(void);
void	ft_usleep(long int time_in_ms);

#endif
