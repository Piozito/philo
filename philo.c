/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:53:01 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/20 16:25:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*par(void *arg)
{
	struct timeval	now;
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->n_philo % 2 == 0)
		usleep(1000);
	while (philo->count_eat != philo->eat_max && *philo->death_flag == 0)
	{
		if (death_check(philo) == 1)
			break ;
		fork_picker(philo);
		safe_print(philo, "is eating");
		custom_usleep(philo, philo->eat);
		gettimeofday(&now, NULL);
		philo->last_eat = get_time(philo->start, now);
		if (death_check(philo) == 1)
			break ;
		fork_dropper(philo);
		safe_print(philo, "is sleeping");
		custom_usleep(philo, philo->sleep);
		if (death_check(philo) == 1)
			break ;
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

void	*impar(void *arg)
{
	t_philo			*philo;
	struct timeval	now;

	philo = (t_philo *)arg;
	if (philo->n_philo % 2 == 1)
		usleep(1000);
	while ((philo->eat_max == -1 || philo->count_eat < philo->eat_max)
		&& *philo->death_flag == 0)
	{
		if (death_check(philo))
			break ;
		impar_helper(philo);
		custom_usleep(philo, philo->eat);
		safe_print(philo, "is eating");
		gettimeofday(&now, NULL);
		philo->last_eat = get_time(philo->start, now);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		custom_usleep(philo, philo->sleep);
		safe_print(philo, "is sleeping");
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

int	parsing(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error("philo takes 4 to 5 arguments.\n"));
	if (parsing(argv) == 1)
		return (ft_error("Invalid arguments.\n"));
	if (ft_atoi(argv[1]) == 1)
		one_philo(argv);
	else
	{
		philo_init(&data, argv);
		while (i < data.n_philos)
			pthread_join(data.philos[i++].trd, NULL);
		i = 0;
		while (i < data.n_philos)
			pthread_mutex_destroy(&data.forks[i++]);
		pthread_mutex_destroy(&data.death_mutex);
		pthread_mutex_destroy(&data.message_mutex);
		free(data.forks);
		free(data.philos);
	}
	return (0);
}
