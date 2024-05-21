/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:54:14 by lconiau           #+#    #+#             */
/*   Updated: 2024/04/19 13:05:59 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_args(t_philo *philo, char **av)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->tt_d = ft_atoi(av[2]);
	philo->tt_e = ft_atoi(av[3]);
	philo->tt_s = ft_atoi(av[4]);
	if (av[5])
		philo->nb_time_to_eat = ft_atoi(av[5]);
	else
		philo->nb_time_to_eat = -1;
}

void	ft_init_philos(t_philo *philos, t_table *table,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meal_eat = 0;
		ft_init_args(&philos[i], av);
		philos[i].start_time = timestamp();
		philos[i].last_meal = timestamp();
		philos[i].print_lock = &table->print_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[0].nb_philo];
		i++;
	}
}

int	ft_create_thread_philo(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	philos;
	int			i;

	if (pthread_create(&philos, NULL, &loop_dead, table->philos) != 0)
		destroy_mutex_init("Thread creation fail", table, forks);
	i = 0;
	while (i < table->philos[0].nb_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]) != 0)
		{
			destroy_mutex_init("Thread creation fail", table, forks);
		}
		i++;
	}
	if (pthread_join(philos, NULL) != 0)
		destroy_mutex_init("Thread join fail", table, forks);
	i = 0;
	while (i < table->philos[0].nb_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			destroy_mutex_init("Thread join fail", table, forks);
		i++;
	}
	return (0);
}

void	ft_init_param(t_table *table, t_philo *philo)
{
	table->dead_flag = 0;
	table->philos = philo;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->print_lock, NULL);
}

void	ft_init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
