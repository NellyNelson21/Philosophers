/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:05 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 18:10:28 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philo(t_table *table, int id)
{
	sem_wait(table->sem_print);
	printf(RED "%lu %d died", get_time_ms() - table->time_start, id);
	printf(RESET "\n");
	sem_post(table->sem_end);
}

static void	*watcher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		sem_wait(philo->sem_time);
		if ((int)(get_time_ms()
			- philo->last_meal_time) > table->input.time_to_die)
			break ;
		sem_post(philo->sem_time);
		usleep(1000);
	}
	kill_philo(table, philo->id);
	return (NULL);
}

static void	philo_routine(t_philo *philo)
{
	int	meals_eaten;

	meals_eaten = 0;
	sem_wait(philo->sem_time);
	philo->last_meal_time = get_time_ms();
	sem_post(philo->sem_time);
	while (1)
	{
		philo_eat(philo);
		++meals_eaten;
		check_fullness(philo->table, meals_eaten);
		philo_sleep(philo);
		philo_think(philo);
	}
}

static int	init_philo_semaphores(t_philo *philo)
{
	char	sem_name_time[256];
	int		n;
	int		i;

	n = philo->id;
	i = -1;
	while ("philo_time"[++i])
		sem_name_time[i] = "philo_time"[i];
	sem_name_time[i++] = '_';
	while (n)
	{
		sem_name_time[i++] = n % 10 + '0';
		n /= 10;
	}
	if (!semaphore_create("philo_forks", 0, &philo->sem_forks)
		|| !semaphore_create("philo_start", 0, &philo->sem_start)
		|| !semaphore_create("philo_end", 0, &philo->sem_end)
		|| !semaphore_create("philo_take", 0, &philo->sem_take)
		|| !semaphore_create("philo_fullness", 0, &philo->sem_fullness)
		|| !semaphore_create("philo_print", 0, &philo->sem_print)
		|| !semaphore_create(sem_name_time, 1, &philo->sem_time))
		return (0);
	return (1);
}

pid_t	start_simulation(t_philo *philo)
{
	pid_t		pid;
	pthread_t	watcher;

	pid = fork();
	if (pid == 0)
	{
		if (!init_philo_semaphores(philo))
		{
			if (philo->sem_end != SEM_FAILED)
				sem_post(philo->sem_end);
			exit(1);
		}
		sem_wait(philo->sem_start);
		philo->last_meal_time = get_time_ms();
		if (pthread_create(&watcher, NULL, watcher_routine, philo))
		{
			sem_post(philo->sem_end);
			exit(1);
		}
		pthread_detach(watcher);
		philo_routine(philo);
		exit(0);
	}
	return (pid);
}
