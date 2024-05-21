/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lconiau <lconiau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:48:26 by lconiau           #+#    #+#             */
/*   Updated: 2024/03/14 10:19:12 by lconiau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				meal_eat;
	size_t			last_meal;
	size_t			tt_d;
	size_t			tt_e;
	size_t			tt_s;
	size_t			start_time;
	int				nb_philo;
	int				nb_time_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}		t_philo;

typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}	t_table;

void		ft_init_args(t_philo *philo, char **av);
void		ft_init_philos(t_philo *philos, t_table *table,
				pthread_mutex_t *forks, char **av);
void		ft_init_forks(pthread_mutex_t *forks, int nb_philo);
int			ft_create_thread_philo(t_table *table, pthread_mutex_t *forks);
void		ft_init_param(t_table *table, t_philo *philo);
void		print_philo(char *msg, t_philo *philo, int id);
long long	timestamp(void);
int			ft_usleep(size_t millisec);
void		destroy_mutex_init(char *str, t_table *table,
				pthread_mutex_t *forks);
int			sleeping(t_philo *philo);
int			check_args(char *argv[]);
int			ft_atoi(char *str);
void		err_msg(char *err_msg);
char		*ft_itoa(long int n);
void		*loop_dead(void *pointer);
int			check_nb_meal(t_philo *philos);
int			check_if_dead(t_philo *philos);
int			check_dead_flag(t_philo *philo);
int			philo_dead(t_philo *philo, size_t tt_d);
void		*routine(void *arg);
void		take_fork(t_philo *philo);
void		grab_and_eat(t_philo *philo, pthread_mutex_t *first_fork,
				pthread_mutex_t *second_fork);
void		ft_just_one(t_philo *philo);
void		thinking(t_philo *philo);
void		check_all_philo(t_table *table);

#endif
