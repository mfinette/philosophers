/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:38:43 by maxime            #+#    #+#             */
/*   Updated: 2023/05/02 11:49:41 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_even(t_philo **tab_philo, t_data *data, int i)
{
	pthread_mutex_lock(&tab_philo[(i + 1) % data->num_of_philo]->fork);
	if (print(tab_philo[i], data, TAKINGFORK) == -1)
		return (pthread_mutex_unlock(&tab_philo[(i + 1) \
		% data->num_of_philo]->fork), -1);
	pthread_mutex_lock(&tab_philo[i]->fork);
	if (print(tab_philo[i], data, TAKINGFORK) == -1)
		return (pthread_mutex_unlock(&tab_philo[i]->fork), \
		pthread_mutex_unlock(&tab_philo[(i + 1) % \
		data->num_of_philo]->fork), -1);
	return (0);
}

int	eat_odd(t_philo **tab_philo, t_data *data, int i)
{
	if (data->num_of_philo % 2 == 1)
		usleep(500 * data->num_of_philo);
	pthread_mutex_lock(&tab_philo[i]->fork);
	if (print(tab_philo[i], data, TAKINGFORK) == -1)
		return (pthread_mutex_unlock(&tab_philo[i]->fork), -1);
	pthread_mutex_lock(&tab_philo[(i + 1) % data->num_of_philo]->fork);
	if (print(tab_philo[i], data, TAKINGFORK) == -1)
		return (pthread_mutex_unlock(&tab_philo[i]->fork) \
		, pthread_mutex_unlock(&tab_philo[(i + 1) \
		% data->num_of_philo]->fork), -1);
	return (0);
}

int	sleeping(t_philo *philo, t_data *data)
{
	if (print(philo, data, SLEEPING) == -1)
		return (-1);
	wait(data->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo, t_data *data)
{
	if (print(philo, data, THINKING) == -1)
		return (-1);
	return (0);
}

int	eating(t_philo **tab_philo, t_data *data, int i)
{
	if (data->num_of_philo == 1)
		return (0);
	if (tab_philo[i]->id % 2 == 1)
	{
		if (eat_odd(tab_philo, data, i) == -1)
			return (-1);
	}
	else if (tab_philo[i]->id % 2 == 0)
	{
		if (eat_even(tab_philo, data, i) == -1)
			return (-1);
	}
	if (print(tab_philo[i], data, EATING) == -1)
		return (pthread_mutex_unlock(&tab_philo[i]->fork), \
		pthread_mutex_unlock(&tab_philo[(i + 1) % \
		data->num_of_philo]->fork), -1);
	pthread_mutex_lock(&data->print);
	tab_philo[i]->last_eat = get_time() - data->start_time;
	tab_philo[i]->eat_count++;
	pthread_mutex_unlock(&data->print);
	wait(data->time_to_eat);
	pthread_mutex_unlock(&tab_philo[i]->fork);
	pthread_mutex_unlock(&tab_philo[(i + 1) % data->num_of_philo]->fork);
	return (0);
}
