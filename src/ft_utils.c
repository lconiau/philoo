/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:55:27 by lconiau           #+#    #+#             */
/*   Updated: 2024/04/19 13:04:28 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_philo(char *msg, t_philo *philo, int id)
{
	size_t	time;

	time = timestamp() - philo->start_time;
	if (!check_dead_flag(philo))
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%06lu %d %s\n", time, id, msg);
		pthread_mutex_unlock(philo->print_lock);
	}
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000LL + t.tv_usec / 1000);
}

int	ft_usleep(size_t millisec)
{
	size_t	start;

	start = timestamp();
	while ((timestamp() - start) < millisec)
	{
		usleep(500);
	}
	return (0);
}

void	destroy_mutex_init(char *str, t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	while (i < table->philos[0].nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	sleeping(t_philo *philo)
{
	print_philo("is sleeping", philo, philo->id);
	ft_usleep(philo->tt_s);
	return (1);
}
