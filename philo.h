/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:49:55 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/16 12:37:22 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
	int				n_philo;
	pthread_t		thread;
	int				last_eat;
	int				count_eat;
	int				eat_max;
	int				eat;
	int				sleep;
	int				die_time;
	int				die_flag;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
}				t_philo;

typedef struct s_data
{
	int			n_philos;
	t_philo		*philos;
	pthread_mutex_t *forks;
	int			eat_max;
}				t_data;


long long	ft_atoi(const char *nptr);
void	philo_init(t_data *data, char **argv);
void	*philo_loop(void *data);



#endif