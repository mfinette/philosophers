/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:17:14 by maxime            #+#    #+#             */
/*   Updated: 2023/05/03 18:11:47 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_starting_point(t_philo *philo)
{
	unsigned long long	start_time;

	pthread_mutex_lock(&philo->data->print);
	start_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->print);
	while (start_time == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		start_time = philo->data->start_time;
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	*life(void	*data_void)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)data_void;
	i = philo->id - 1;
	get_starting_point(philo);
	if (philo->id % 2 == 1)
	{
		if (thinking(philo, philo->data) == -1)
			return (NULL);
		custom_usleep(philo->data->time_to_eat / 20);
		// custom_usleep(100 * philo->data->num_of_philo);
	}
	while (1)
	{
		if (eating(philo->data->tab_philo, philo->data, i) == -1)
			return (NULL);
		if (sleeping(philo, philo->data) == -1)
			return (NULL);
		if (thinking(philo, philo->data) == -1)
			return (NULL);
	}
	return (NULL);
}

void	live_life(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&data->tab_philo[i]->thread_id, \
		NULL, life, data->tab_philo[i]);
		i++;
	}
	pthread_mutex_lock(&data->print);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->print);
	if (monitoring(data) == -1)
	{
		pthread_mutex_lock(&data->print);
		data->end = 1;
		pthread_mutex_unlock(&data->print);
	}
	while (i > 0)
	{
		pthread_join(data->tab_philo[i - 1]->thread_id, NULL);
		i--;
	}
}
