/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:56:55 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/26 21:56:57 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_structs(pthread_t *thread, pthread_mutex_t *forks,
		pthread_mutex_t *meals_lock, t_philosoper *philosophers)
{
	free(thread);
	free(forks);
	free(meals_lock);
	if (philosophers->philo_dead == 1)
	{
		free(philosophers);
		return (1);
	}
	free(philosophers);
	return (0);
}
