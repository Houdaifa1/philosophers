/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:56:43 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/27 00:09:07 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate(pthread_t **thread, pthread_mutex_t **forks,
		pthread_mutex_t **meals_lock, t_data data)
{
	int	j;

	*thread = malloc(sizeof(pthread_t) * (data.num_of_philos));
	*forks = malloc(sizeof(pthread_mutex_t) * (data.num_of_philos));
	*meals_lock = malloc(sizeof(pthread_mutex_t) * (data.num_of_philos));
	if (!*thread || !*forks || !*meals_lock)
		return (1);
	j = 0;
	while (j < data.num_of_philos)
	{
		pthread_mutex_init(&(*forks)[j], NULL);
		pthread_mutex_init(&(*meals_lock)[j], NULL);
		j++;
	}
	return (0);
}

int	allocate_for_structs(t_hold *hold, t_data data, pthread_mutex_t *stop)
{
	pthread_t		*thread;
	t_philosoper	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meals_lock;

	thread = NULL;
	philosophers = NULL;
	forks = NULL;
	meals_lock = NULL;
	hold->philosophers = philosophers;
	hold->forks = forks;
	hold->thread = thread;
	hold->meals_lock = meals_lock;
	hold->philosophers = malloc(sizeof(t_philosoper) * (data.num_of_philos));
	if (!hold->philosophers)
		return (1);
	if (allocate(&hold->thread, &hold->forks, &hold->meals_lock, data) == 1)
		return (1);
	pthread_mutex_init(&(*stop), NULL);
	return (0);
}

void	initial_philos(t_philosoper *philosophers, int i, t_data data,
		struct timeval start)
{
	philosophers->philo_id = i + 1;
	philosophers->time_sec = start.tv_sec;
	philosophers->time_usec = start.tv_usec;
	philosophers->num_of_philos = data.num_of_philos;
	philosophers->time_to_die = data.time_to_die;
	philosophers->time_to_sleep = data.time_to_sleep * 1000;
	philosophers->time_to_eat = data.time_to_eat * 1000;
	philosophers->last_meal = 0;
	philosophers->eat = 0;
	philosophers->philo_dead = 0;
	philosophers->philos_full = 0;
	philosophers->meals_num = 0;
	philosophers->change = 1;
	philosophers->max_meals = data.max_meals;
}

void	give_forks(t_philosoper *philosophers, pthread_mutex_t *forks,
		pthread_mutex_t *meals_lock, int i)
{
	if (philosophers->num_of_philos == 1)
	{
		philosophers->left_fork = &forks[i];
		philosophers->meals_lock = &meals_lock[i];
		return ;
	}
	if ((i + 1) == philosophers->num_of_philos)
		philosophers->left_fork = &forks[0];
	else
		philosophers->left_fork = &forks[i + 1];
	philosophers->right_fork = &forks[i];
	philosophers->meals_lock = &meals_lock[i];
}

int	join_destroy(pthread_t *thread, pthread_mutex_t *forks,
		pthread_mutex_t *meals_lock, t_philosoper *philos)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philos->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&meals_lock[i]);
		i++;
	}
	if (free_structs(thread, forks, meals_lock, philos) == 1)
		return (1);
	return (0);
}
