/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:53:01 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/16 17:09:59 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*loop(void *arg)
{
	struct timeval	now;
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (philo->count_eat != philo->eat_max && *philo->death_flag == 0)
	{
		if (death_check(philo) == 1)
			break ;
		fork_picker(philo);
		if (death_check(philo) == 1)
			break ;
		usleep(philo->eat);
		safe_print(philo, "is eating");
		gettimeofday(&now, NULL);
		philo->last_eat = get_time(philo->start, now);
		if (death_check(philo) == 1)
			break ;
		fork_dropper(philo);
		usleep(philo->sleep);
		if (death_check(philo) == 1)
			break ;
		safe_print(philo, "is sleeping");
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

void	one_philo(char **argv)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(argv[2]));
	printf("%lld 1 died\n", ft_atoi(argv[2]));
	return ;
}

int	parsing(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
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
			pthread_join(data.philos[i++].thread, NULL);
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
