/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:58:17 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/27 17:14:57 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_flag(t_philosoper *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philos->stop_mutex);
	if (philos->shared->stop_flag)
	{
		pthread_mutex_unlock(philos->stop_mutex);
		i = 1;
	}
	else
		pthread_mutex_unlock(philos->stop_mutex);
	return (i);
}

int	check_flag_unlock_two(t_philosoper *philos)
{
	size_t	time_now;

	if (philos->philo_id % 2 != 0)
		pthread_mutex_lock(philos->right_fork);
	else
		pthread_mutex_lock(philos->left_fork);
	pthread_mutex_lock(philos->stop_mutex);
	if (philos->shared->stop_flag)
	{
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->stop_mutex);
	pthread_mutex_lock(philos->meals_lock);
	time_now = get_time_inmill(philos->time_sec, philos->time_usec);
	printf("%ld      %d   has taken a fork\n", time_now, philos->philo_id);
	printf("%ld      %d   is eating\n", time_now, philos->philo_id);
	philos->last_meal = time_now;
	philos->meals_num++;
	philos->eat = 1;
	pthread_mutex_unlock(philos->meals_lock);
	return (0);
}

int	check_flag_unlock_one_and_two(t_philosoper *philos)
{
	size_t	time_now;

	if (check_flag(philos) == 1)
		return (1);
	if (philos->philo_id % 2 != 0)
		pthread_mutex_lock(philos->left_fork);
	else
		pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(philos->stop_mutex);
	if (philos->shared->stop_flag)
	{
		if (philos->philo_id % 2 != 0)
			pthread_mutex_unlock(philos->left_fork);
		else
			pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->stop_mutex);
	time_now = get_time_inmill(philos->time_sec, philos->time_usec);
	printf("%ld      %d   has taken a fork\n", time_now, philos->philo_id);
	if (check_if_one_philo(philos) == 1 || check_flag_unlock_two(philos) == 1)
		return (1);
	return (0);
}

int	sleep_and_check(t_philosoper *philos, int j, size_t time)
{
	size_t	i;

	i = 0;
	while (i++ < time / 10000)
	{
		pthread_mutex_lock(philos->stop_mutex);
		if (philos->shared->stop_flag)
		{
			pthread_mutex_unlock(philos->stop_mutex);
			{
				if (j == 0)
					return (1);
				pthread_mutex_unlock(philos->right_fork);
				pthread_mutex_unlock(philos->left_fork);
				return (1);
			}
		}
		pthread_mutex_unlock(philos->stop_mutex);
		usleep(10000);
	}
	if (j == 0)
		return (0);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
	return (0);
}

int	sleep_and_think(t_philosoper *philos)
{
	size_t	time_now;

	time_now = get_time_inmill(philos->time_sec, philos->time_usec);
	if (check_flag(philos) == 1)
		return (1);
	printf("%ld      %d   is sleeping\n", time_now, philos->philo_id);
	if (sleep_and_check(philos, 0, philos->time_to_sleep) == 1)
		return (1);
	time_now = get_time_inmill(philos->time_sec, philos->time_usec);
	if (check_flag(philos) == 1)
		return (1);
	printf("%ld      %d   is thinking\n", time_now, philos->philo_id);
	if (philos->time_to_eat > philos->time_to_sleep)
		usleep(philos->time_to_eat - philos->time_to_sleep + 1000);
	usleep(1000);
	return (0);
}
