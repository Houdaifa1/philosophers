/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:57:30 by hdrahm            #+#    #+#             */
/*   Updated: 2024/07/26 21:57:32 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_lenght(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		i++;
		count++;
	}
	if (count > 10)
		return (1);
	return (0);
}

long	ft_atoi(char *str)
{
	int		i;
	long	outcome;

	i = 0;
	outcome = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (-1);
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_lenght(str, i) == 1)
			return (-1);
		outcome = outcome * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || outcome == 0 || outcome > 2147483647)
		return (-1);
	return (outcome);
}
