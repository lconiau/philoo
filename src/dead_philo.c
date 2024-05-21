/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:55:19 by lconiau           #+#    #+#             */
/*   Updated: 2024/04/19 12:57:01 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_dead(t_philo *philo, size_t tt_d)
{
	pthread_mutex_lock(philo->meal_lock);
	if (timestamp() - philo->last_meal >= tt_d && philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	return (pthread_mutex_unlock(philo->dead_lock), 0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philo)
	{
		if (philo_dead(&philos[i], philos[i].tt_d))
		{
			print_philo("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nb_meal(t_philo *philos)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].nb_time_to_eat == -1)
		return (0);
	while (i < philos[0].nb_philo)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meal_eat >= philos[i].nb_time_to_eat)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == philos[0].nb_philo)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*loop_dead(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (check_dead_flag(philos) == 0 || check_nb_meal(philos) == 0)
	{
		if (check_if_dead(philos) == 1 || check_nb_meal(philos) == 1)
			break ;
	}
	return (pointer);
}
