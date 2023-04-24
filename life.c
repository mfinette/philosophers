/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:17:14 by maxime            #+#    #+#             */
/*   Updated: 2023/04/24 12:42:04 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_philo *philo)
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

void	*routine(void	*data_void)
{
	int			i;
	t_philo		*philo;

	philo = (t_philo *)data_void;
	i = philo->id - 1;
	wait_all_threads(philo);
	usleep(100 * philo->data->num_of_philo);
	while (1)
	{
		if (thinking(philo, philo->data) == -1)
			return (NULL);
		if (eating(philo->data->tab_philo, philo->data, i) == -1)
			return (NULL);
		if (sleeping(philo, philo->data) == -1)
			return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&data->tab_philo[i]->thread_id, \
		NULL, routine, data->tab_philo[i]);
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
