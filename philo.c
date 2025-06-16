/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:53:01 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/16 12:49:43 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	philo_init(t_data *data, char **argv)
{
	int	i;

	data->n_philos = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if(argv[5])
		data->eat_max = ft_atoi(argv[5]);
	else
		data->eat_max = -1;
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].n_philo = i + 1;
		data->philos[i].fork_left = data->forks[i];
		if(i == data->n_philos)
			data->philos[i].fork_right = data->forks[0];
		else
			data->philos[i].fork_right = data->forks[(i + 1) % data->n_philos];
		data->philos[i].eat = ft_atoi(argv[3]);
		data->philos[i].sleep = ft_atoi(argv[4]);
		data->philos[i].die_time = ft_atoi(argv[2]);
		data->philos[i].die_flag = 0;
		data->philos[i].count_eat = 0;
		data->philos[i].eat_max = data->eat_max;
		pthread_create(&data->philos[i].thread, NULL, philo_loop, &data->philos[i]);
		i++;
	}
}

void *philo_loop(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while(philo->count_eat != philo->eat_max)
	{
		pthread_mutex_lock(&philo->fork_left);
		pthread_mutex_lock(&philo->fork_right);
		philo->count_eat++;
		printf("id: %d | eat: %d | philosopher is eating\n", philo->n_philo, philo->count_eat);
		usleep(philo->eat);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(&philo->fork_right);
		printf("id: %d | philosopher is sleeping\n", philo->n_philo);
		usleep(philo->sleep);
		printf("id: %d | philosopher is thinking\n", philo->n_philo);
	}
	return arg;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("philo takes 4 to 5 arguments.\n");
		return (1);
	}
	philo_init(&data, argv);
	philo_loop(&data);
	while (i < data.n_philos)
		pthread_join(data.philos[i++].thread, NULL);
	while (i < data.n_philos)
		pthread_mutex_destroy(&data.forks[i++]);
	free(data.forks);
	free(data.philos);
	return (0);
}