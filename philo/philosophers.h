/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:58:05 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/27 17:02:39 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared
{
	int				stop_flag;
}					t_shared;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			max_meals;
	pthread_mutex_t	stop;
	struct timeval	start;
	t_shared		shared;

}					t_data;

typedef struct s_philosopher
{
	int				philo_id;
	long			time_sec;
	long			time_usec;
	long			last_meal;
	long			meals_num;
	long			max_meals;
	int				philos_full;
	int				eat;
	int				philo_dead;
	long			change;
	t_shared		*shared;
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meals_lock;
	pthread_mutex_t	*stop_mutex;

}					t_philosoper;

typedef struct s_hold
{
	t_philosoper	*philosophers;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meals_lock;

}					t_hold;

long				ft_atoi(char *str);
int					check_flag_unlock_one_and_two(t_philosoper *philos);
int					check_if_one_philo(t_philosoper *philo);
int					sleep_and_check(t_philosoper *philos, int j, size_t time);
int					sleep_and_think(t_philosoper *philos);
size_t				get_time_inmill(long old_time_sec, long old_time_usec);
int					check_flag(t_philosoper *philos);
int					check_flag_unlock_two(t_philosoper *philos);
int					check_death(t_philosoper *philos, int i, size_t time_now);
int					check_meals_eaten(t_philosoper *philos, int i);
int					allocate_for_structs(t_hold *hold, t_data data,
						pthread_mutex_t *stop);
int					allocate(pthread_t **thread, pthread_mutex_t **forks,
						pthread_mutex_t **meals_lock, t_data data);
void				initial_philos(t_philosoper *philosophers, int i,
						t_data data, struct timeval start);
void				give_forks(t_philosoper *philosophers,
						pthread_mutex_t *forks, pthread_mutex_t *meals_lock,
						int i);
int					join_destroy(pthread_t *thread, pthread_mutex_t *forks,
						pthread_mutex_t *meals_lock, t_philosoper *philos);
int					free_structs(pthread_t *thread, pthread_mutex_t *forks,
						pthread_mutex_t *meals_lock,
						t_philosoper *philosophers);

#endif
