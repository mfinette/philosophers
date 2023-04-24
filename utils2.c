/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:51:43 by maxime            #+#    #+#             */
/*   Updated: 2023/04/24 12:53:29 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_data	*data)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_lock(&data->print);
			if (is_dead(data->tab_philo[i], data))
				return (-1);
			count += has_eaten_enough(data->tab_philo[i]);
			pthread_mutex_unlock(&data->print);
			i++;
		}
		if (count == data->num_of_philo)
			return (-1);
	}
}

int	has_eaten_enough(t_philo *philo)
{
	if (philo->data->num_of_must_eat == -1)
		return (0);
	if (philo->eat_count < philo->data->num_of_must_eat)
		return (0);
	return (1);
}