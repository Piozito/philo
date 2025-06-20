/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:49:55 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/20 16:32:06 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n_philo;
	pthread_t		trd;
	long			last_eat;
	int				count_eat;
	int				eat_max;
	int				eat;
	int				sleep;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*message_mutex;
	int				*death_flag;
	int				die_time;
	struct timeval	start;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}				t_philo;

typedef struct s_data
{
	int				n_philos;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				eat_max;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	message_mutex;
	int				death_flag;
}				t_data;

void		*par(void *data);
int			ft_isdigit(int c);
void		*impar(void *data);
int			parsing(char **argv);
void		one_philo(char **argv);
long long	ft_atoi(const char *nptr);
int			death_check(t_philo *philo);
void		fork_picker(t_philo *philo);
void		fork_dropper(t_philo *philo);
void		impar_helper(t_philo *philo);
void		philo_init(t_data *data, char **argv);
void		safe_print(t_philo *philo, char *str);
void		init_helper(t_data *data, char **argv);
void		custom_usleep(t_philo *philo, long usec);
long		get_time(struct timeval start, struct timeval now);

#endif