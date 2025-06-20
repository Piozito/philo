/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:10:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/20 16:26:32 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_helper(t_data *data, char **argv)
{
	int				i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].n_philo = i + 1;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->n_philos];
		data->philos[i].eat = ft_atoi(argv[3]);
		data->philos[i].sleep = ft_atoi(argv[4]);
		data->philos[i].die_time = ft_atoi(argv[2]);
		data->philos[i].count_eat = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].eat_max = data->eat_max;
		data->philos[i].death_flag = &data->death_flag;
		data->philos[i].death_mutex = &data->death_mutex;
		data->philos[i].message_mutex = &data->message_mutex;
		gettimeofday(&data->philos[i].start, NULL);
		if (data->n_philos % 2 == 0)
			pthread_create(&data->philos[i].trd, NULL, par, &data->philos[i]);
		else
			pthread_create(&data->philos[i].trd, NULL, impar, &data->philos[i]);
		i++;
	}
}

void	fork_picker(t_philo *philo)
{
	if (philo->n_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		safe_print(philo, "has taken a fork");
	}
}

void	fork_dropper(t_philo *philo)
{
	if (philo->n_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

int	death_check(t_philo *philo)
{
	struct timeval	now;

	pthread_mutex_lock(philo->death_mutex);
	gettimeofday(&now, NULL);
	if (get_time(philo->start, now) - philo->last_eat > philo->die_time)
	{
		safe_print(philo, "died");
		*philo->death_flag = 1;
		fork_dropper(philo);
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}
