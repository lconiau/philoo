/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:59:22 by lconiau           #+#    #+#             */
/*   Updated: 2024/05/21 15:41:12 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
}

void	ft_just_one(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
	ft_usleep(philo->tt_d);
	pthread_mutex_unlock(philo->r_fork);
	return ;
}

void	grab_and_eat(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_philo("has taken a fork", philo, philo->id);
	pthread_mutex_lock(second_fork);
	print_philo("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_philo("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = timestamp();
	philo->meal_eat += 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->tt_e);
	philo->eating = 0;
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->r_fork < philo->l_fork)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	grab_and_eat(philo, first_fork, second_fork);
	ft_usleep(1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(0.9 * philo->tt_e);
	if (philo->nb_philo == 1)
		ft_just_one(philo);
	while (!check_dead_flag(philo))
	{
		take_fork(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
