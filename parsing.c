/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:40:18 by maxime            #+#    #+#             */
/*   Updated: 2023/05/02 11:31:14 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc > 6 || argc < 5)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		if (!check_str(argv[1]))
			return (0);
		i++;
	}
	return (1);
}

void	init_one_philo(t_philo *philo, t_data *data, int philo_index)
{
	philo->id = philo_index + 1;
	philo->eat_count = 0;
	philo->data = data;
	pthread_mutex_init(&philo->fork, NULL);
	philo->last_eat = 0;
}

int	init_all_philo(t_data *data)
{
	int		philo_index;

	data->tab_philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->tab_philo)
		return (-1);
	philo_index = 0;
	while (philo_index < data->num_of_philo)
	{
		data->tab_philo[philo_index] = malloc(sizeof(t_philo));
		if (!data->tab_philo[philo_index])
			return (-1);
		init_one_philo(data->tab_philo[philo_index], data, philo_index);
		philo_index++;
	}
	return (0);
}

t_data	*parse_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_of_must_eat = -1;
	if (argc == 6)
		data->num_of_must_eat = ft_atoi(argv[5]);
	data->end = 0;
	data->start_time = 0;
	pthread_mutex_init(&data->print, NULL);
	if (init_all_philo(data) == -1)
		return (free(data), NULL);
	return (data);
}
