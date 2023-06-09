/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:06 by maxime            #+#    #+#             */
/*   Updated: 2023/05/04 11:07:07 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	long long int	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != ((result * 10 + (sign * (str[i] - '0'))) / 10))
			return ((int)((sign + 1) / 2 / -1));
		result = result * 10;
		result = result + (str[i] - 48) * sign;
		i++;
	}
	return ((int)result);
}

unsigned long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	print(t_philo *philo, t_data *data, int state)
{
	pthread_mutex_lock(&data->print);
	if (data->end)
		return (pthread_mutex_unlock(&data->print), -1);
	if (state == THINKING && !data->end)
		printf("%llu %d is thinking\n", get_time() \
		- data->start_time, philo->id);
	if (state == EATING && !data->end)
		printf("%llu %d is eating\n", get_time() \
		- data->start_time, philo->id);
	if (state == SLEEPING && !data->end)
		printf("%llu %d is sleeping\n", get_time() \
		- data->start_time, philo->id);
	if (state == DEAD && !data->end)
		printf("%llu %d died\n", get_time() \
		- data->start_time, philo->id);
	if (state == TAKINGFORK && !data->end)
		printf("%llu %d has taken a fork\n", get_time() \
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	return (0);
}
