/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:38:19 by maxime            #+#    #+#             */
/*   Updated: 2023/04/24 15:47:31 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int argc, char **argv)
{
	t_data	data;

    (void)data;
	if (!check_args(argc, argv))
		return (printf("error\n"), 1);
	data = parse_data(argc, argv);
	start_simulation(&data);
	// free_data(data);
	return (0);
}
