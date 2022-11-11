/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:45:03 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 17:27:14 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

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
	t_input	input;
	size_t	time_start;
	sem_t	*sem_forks;
	sem_t	*sem_fullness;
	sem_t	*sem_print;
	sem_t	*sem_start;
	sem_t	*sem_end;
	sem_t	*sem_take;
}	t_table;

typedef struct s_philo {
	int		id;
	size_t	last_meal_time;
	size_t	time_start;
	sem_t	*sem_forks;
	sem_t	*sem_fullness;
	sem_t	*sem_print;
	sem_t	*sem_start;
	sem_t	*sem_end;
	sem_t	*sem_take;
	sem_t	*sem_time;
	t_table	*table;
}	t_philo;

//initialisation_func
int		process_arg(char *arg);
int		init(int argc, char **argv, t_table *table, pid_t **pids);

//semaphore_func
int		semaphore_create(const char *name, int value, sem_t **sem);

//custom_time_func
size_t	get_time_ms(void);
void	ms_sleep(int t_ms);

//philo_actions_func
void	check_fullness(t_table *table, int meals_eaten);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//print_func
void	print_message(char *str, t_philo *philo);

//simulation_func
void	destroy_philos(int n, pid_t *philos);
int		finish_simulation(t_table *table, pid_t *philos);
pid_t	start_simulation(t_philo *philo);

#endif