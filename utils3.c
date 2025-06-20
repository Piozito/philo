/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:40:38 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/20 16:26:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	custom_usleep(t_philo *philo, long ms)
{
	struct timeval	start;
	struct timeval	now;
	long			elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < ms && *philo->death_flag == 0)
	{
		usleep(1000);
		if (death_check(philo))
			break ;
		gettimeofday(&now, NULL);
		elapsed = get_time(start, now);
	}
}

void	one_philo(char **argv)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(argv[2]));
	printf("%lld 1 died\n", ft_atoi(argv[2]));
	return ;
}

void	impar_helper(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	safe_print(philo, "has taken a fork");
}
