/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:57:53 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/27 20:08:21 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_monitor(void *philo)
{
	t_philosoper	*philos;
	int				i;
	size_t			time_now;

	philos = (t_philosoper *)philo;
	while (1)
	{
		i = 0;
		while (i < philos->num_of_philos)
		{
			time_now = get_time_inmill(philos->time_sec, philos->time_usec);
			pthread_mutex_lock(philos[i].meals_lock);
			if (check_death(philos, i, time_now) == 1)
				return (NULL);
			pthread_mutex_unlock(philos[i].meals_lock);
			if (check_meals_eaten(philos, i) == 1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	*table(void *philo)
{
	t_philosoper	*philos;

	philos = (t_philosoper *)philo;
	while (1)
	{
		if (philos->philo_id % 2 == (philos->change % 2))
		{
			if (check_flag_unlock_one_and_two(philos) == 1)
				break ;
			if (sleep_and_check(philos, 1, philos->time_to_eat) == 1)
				break ;
		}
		else if (philos->eat == 0)
		{
			if (sleep_and_check(philos, 0, philos->time_to_eat) == 1)
				break ;
		}
		else
		{
			if (sleep_and_think(philos) == 1)
				break ;
		}
		philos->change++;
	}
	return (NULL);
}

int	create_join_monitor(t_philosoper *philosophers)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, ft_monitor, philosophers) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}

int	ft_create_threads(t_data data, pthread_mutex_t stop, t_shared shared,
		struct timeval start)
{
	t_hold	hold;
	int		i;

	gettimeofday(&start, NULL);
	if (allocate_for_structs(&hold, data, &stop) == 1)
		return (1);
	i = -1;
	shared.stop_flag = 0;
	while (++i < data.num_of_philos)
	{
		initial_philos(&hold.philosophers[i], i, data, start);
		give_forks(&hold.philosophers[i], hold.forks, hold.meals_lock, i);
		hold.philosophers[i].shared = &shared;
		hold.philosophers[i].stop_mutex = &stop;
		if (pthread_create(&hold.thread[i], NULL, table,
				&hold.philosophers[i]) != 0)
			return (1);
	}
	if (create_join_monitor(hold.philosophers) == 1)
		return (1);
	if (join_destroy(hold.thread, hold.forks, hold.meals_lock,
			hold.philosophers) == 1)
		return (1);
	pthread_mutex_destroy(&stop);
	return (0);
}

int	main(int arc, char **arv)
{
	t_data	data;

	if (arc == 5 || arc == 6)
	{
		if (ft_atoi(arv[1]) == -1 || ft_atoi(arv[2]) == -1 || ft_atoi(arv[3])
			== -1 || ft_atoi(arv[4]) == -1)
			return (1);
		data.num_of_philos = ft_atoi(arv[1]);
		data.time_to_die = ft_atoi(arv[2]);
		data.time_to_eat = ft_atoi(arv[3]);
		data.time_to_sleep = ft_atoi(arv[4]);
		if (arc == 5)
			data.max_meals = -1;
		else
		{
			if (ft_atoi(arv[5]) == -1)
				return (1);
			data.max_meals = ft_atoi(arv[5]);
		}
		return (ft_create_threads(data, data.stop, data.shared, data.start));
	}
	return (1);
}
