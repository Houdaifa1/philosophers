/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:57:40 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/27 17:02:15 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosoper *philos, int i, size_t time_now)
{
	if (time_now - philos[i].last_meal > philos->time_to_die)
	{
		printf("%ld       %d     died\n", time_now, i + 1);
		pthread_mutex_lock(philos[i].stop_mutex);
		philos->philo_dead = 1;
		philos->shared->stop_flag = 1;
		pthread_mutex_unlock(philos[i].stop_mutex);
		pthread_mutex_unlock(philos[i].meals_lock);
		return (1);
	}
	return (0);
}

int	check_meals_eaten(t_philosoper *philos, int i)
{
	int	j;
	int	check;

	j = 0;
	check = 0;
	while (j < philos->num_of_philos && philos[i].max_meals != -1)
	{
		pthread_mutex_lock(philos[j].meals_lock);
		if (philos[j].meals_num < philos[j].max_meals)
			check = 1;
		pthread_mutex_unlock(philos[j].meals_lock);
		j++;
	}
	if (check == 0 && philos[i].max_meals != -1)
	{
		pthread_mutex_lock(philos[i].stop_mutex);
		philos->philos_full = 1;
		philos->shared->stop_flag = 1;
		pthread_mutex_unlock(philos[i].stop_mutex);
		return (1);
	}
	return (0);
}

size_t	get_time_inmill(long old_time_sec, long old_time_usec)
{
	struct timeval	now;
	size_t			time_now;

	gettimeofday(&now, NULL);
	time_now = (now.tv_sec - old_time_sec) * 1000 + (now.tv_usec
			- old_time_usec) / 1000;
	return (time_now);
}

int	check_if_one_philo(t_philosoper *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}
