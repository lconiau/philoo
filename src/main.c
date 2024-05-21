/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:55:13 by lconiau           #+#    #+#             */
/*   Updated: 2024/04/19 13:07:11 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error_msg(char *msg)
{
	printf("Error : %s\n", msg);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo			philo[MAX_PHILO];
	t_table			table;
	pthread_mutex_t	forks[MAX_PHILO];

	if (!check_args(argv))
		return (1);
	if (argc == 5 || argc == 6)
	{
		ft_init_param(&table, philo);
		ft_init_forks(forks, ft_atoi(argv[1]));
		ft_init_philos(philo, &table, forks, argv);
		ft_create_thread_philo(&table, forks);
		destroy_mutex_init(NULL, &table, forks);
	}
	else
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	return (0);
}
