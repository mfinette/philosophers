/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:38:19 by maxime            #+#    #+#             */
/*   Updated: 2023/05/02 11:31:28 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->tab_philo[i]->fork);
		free(data->tab_philo[i]);
		i++;
	}
	free(data->tab_philo);
}

void	free_data(t_data *data)
{
	free_all_philo(data);
	pthread_mutex_destroy(&data->print);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
		return (printf("error\n"), 1);
	data = parse_data(argc, argv);
	if (!data)
		return (printf("error\n"), 1);
	live_life(data);
	free_data(data);
	return (0);
}
