/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:43:55 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/20 16:26:17 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	ft_atoi(const char *nptr)
{
	int			i;
	long long	number;
	int			sinal;

	i = 0;
	number = 0;
	sinal = 1;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sinal *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = (number * 10) + (nptr[i] - '0');
		i++;
	}
	number *= sinal;
	return (number);
}

size_t	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	philo_init(t_data *data, char **argv)
{
	int	i;

	data->n_philos = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data->death_flag = 0;
	if (argv[5])
		data->eat_max = ft_atoi(argv[5]);
	else
		data->eat_max = -1;
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->message_mutex, NULL);
	init_helper(data, argv);
}

long	get_time(struct timeval start, struct timeval now)
{
	long	seconds;
	long	milliseconds;

	seconds = (now.tv_sec - start.tv_sec) * 1000L;
	milliseconds = (now.tv_usec - start.tv_usec) / 1000L;
	return (seconds + milliseconds);
}

void	safe_print(t_philo *philo, char *str)
{
	struct timeval	now;

	pthread_mutex_lock(philo->message_mutex);
	gettimeofday(&now, NULL);
	if (ft_strcmp(str, "is eating") == 0)
		philo->count_eat++;
	if (!(*philo->death_flag))
		printf("%ld %d %s\n", get_time(philo->start, now), philo->n_philo, str);
	pthread_mutex_unlock(philo->message_mutex);
}
