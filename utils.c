/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:06 by maxime            #+#    #+#             */
/*   Updated: 2023/04/24 12:46:56 by maxime           ###   ########.fr       */
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

void	wait(unsigned long long time_ms)
{
	unsigned long long	time;

	time = get_time();
	usleep(time_ms * 900);
	while (get_time() - time < time_ms)
		usleep(100);
}

int	print(t_philo *philo, t_data *data, int state)
{
	pthread_mutex_lock(&data->print);
	if (data->end)
		return (pthread_mutex_unlock(&data->print), -1);
	if (state == THINKING && !data->end)
		printf("\e[033m%llu %d is thinking\e[0m\n", get_time() \
		- data->start_time, philo->id);
	if (state == EATING && !data->end)
		printf("\e[031m%llu %d is eating\e[0m\n", get_time() \
		- data->start_time, philo->id);
	if (state == SLEEPING && !data->end)
		printf("\e[034m%llu %d is sleeping\e[0m\n", get_time() \
		- data->start_time, philo->id);
	if (state == DEAD && !data->end)
		printf("\e[41m%llu %d died\e[0m\n", get_time() \
		- data->start_time, philo->id);
	if (state == 42 && !data->end)
		printf("\e[0;32m%llu %d has taken a fork\e[0m\n", get_time() \
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print);
	return (0);
}
