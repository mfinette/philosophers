/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:54:05 by maxime            #+#    #+#             */
/*   Updated: 2023/05/04 11:30:31 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, t_data *data)
{
	if (get_time() - data->start_time > philo->last_eat + data->time_to_die)
	{
		pthread_mutex_unlock(&data->print);
		print(philo, data, DEAD);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->print);
	if (data->end == 1)
		return (pthread_mutex_unlock(&data->print), 1);
	pthread_mutex_unlock(&data->print);
	return (0);
}
