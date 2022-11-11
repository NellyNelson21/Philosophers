/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:02:42 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 17:21:28 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[1m\033[31m"
# define RESET "\033[0m"

typedef struct s_input
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_input;

typedef struct s_table
{
	int				ok;
	int				num_full_philos;
	size_t			time_start;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_fullness;
	pthread_mutex_t	*m_forks;
	t_input			input;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				last_meal_time;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	m_start;
	pthread_mutex_t	m_time;
	t_table			*table;
}	t_philo;

//initialisation_func
int		process_arg(char *arg);
int		init(int argc, char **argv, t_table *table, t_philo **philos);

//custom_time_func
size_t	get_time_ms(void);
void	ms_sleep(int t_ms);

//print_func
void	print_error(char *message, pthread_mutex_t *mutex);
void	print_message(char *message, t_philo *philo);

//philo_actions_func
void	check_fullness(t_table *table, int meals_eaten);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//simulation_func
int		create_threads(int n, t_philo *philos);
int		is_simulation_finished(t_table *table);
int		finish_simulation(t_table *table, t_philo *philos);

#endif