/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:13:08 by maxime            #+#    #+#             */
/*   Updated: 2023/05/03 17:43:42 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <assert.h>
# include <time.h>
# include <sys/time.h>

/* PHILO MESSAGES*/
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

/* PHILO STATES */
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define TAKINGFORK 5

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t				thread_id;
	int						id;
	unsigned long long		last_eat;
	int						eat_count;
	t_data					*data;
	pthread_mutex_t			fork ;
}			t_philo;

typedef struct s_data
{
	unsigned long long		start_time;
	int						num_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						num_of_must_eat;
	int						end;
	t_philo					**tab_philo;
	pthread_mutex_t			print;
}			t_data;

/* PARSING */
int					check_args(int argc, char **argv);
t_data				*parse_data(int argc, char **argv);
int					check_args(int argc, char **argv);
int					check_str(char *str);

/* INITIALIZATION */
int					init_all_philo(t_data *data);
void				init_one_philo(t_philo *philo, t_data *data, \
int philo_index);

/* STATES */
int					eat_even(t_philo **tab_philo, t_data *data, int i);
int					eat_odd(t_philo **tab_philo, t_data *data, int i);
int					sleeping(t_philo *philo, t_data *data);
int					thinking(t_philo *philo, t_data *data);
int					eating(t_philo **tab_philo, t_data *data, int i);

/* UTILS */
int					ft_atoi(const char *str);
void				wait(unsigned long long time_ms);
unsigned long long	get_time(void);
int					print(t_philo *philo, t_data *data, int state);
int					monitoring(t_data	*data);
int					has_eaten_enough(t_philo *philo);
void				custom_usleep(unsigned long long time_in_us);
void	wait(unsigned long long time_ms);

/* LIFE */
void				get_starting_point(t_philo *philo);
void				*life(void	*data_void);
void				live_life(t_data *data);

/* DEATH */
int					is_dead(t_philo *philo, t_data *data);
int					check_death(t_data *data);

#endif