/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnelson <nnelson@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:04:52 by andreys           #+#    #+#             */
/*   Updated: 2022/07/19 13:23:48 by nnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_finished(t_table *table)
{
	return (!table->ok || (table->input.num_times_to_eat != -1
			&& table->num_full_philos == table->input.num_of_philos));
}

static void	kill_philo(t_table *table, int id)
{
	if (is_simulation_finished(table))
		return ;
	pthread_mutex_lock(&table->m_print);
	printf(RED "%lu %i died", get_time_ms() - table->time_start, id);
	printf(RESET "\n");
	table->ok = 0;
}

static void	*simulation_watcher(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (!is_simulation_finished(table))
	{
		pthread_mutex_lock(&philo->m_time);
		if ((int)(get_time_ms() - philo->last_meal_time)
			> table->input.time_to_die)
			break ;
		pthread_mutex_unlock(&philo->m_time);
		usleep(500);
	}
	kill_philo(table, philo->id);
	return (NULL);
}

static void	*simulation(void *arg)
{
	pthread_t	watcher;
	t_philo		*philo;
	int			meals_eaten;

	meals_eaten = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->m_start);
	pthread_mutex_lock(&philo->m_time);
	if (is_simulation_finished(philo->table))
		return (NULL);
	if (pthread_create(&watcher, NULL, simulation_watcher, philo))
		return (NULL);
	pthread_detach(watcher);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->m_time);
	while (!is_simulation_finished(philo->table))
	{
		philo_eat(philo);
		meals_eaten++;
		check_fullness(philo->table, meals_eaten);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_mutex_unlock(&philo->m_start);
	return (NULL);
}

int	create_threads(int n, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (pthread_create(&philos[i].thread, NULL, simulation, philos + i))
		{
			print_error("Error: thread creation.\n", &philos[i].table->m_print);
			return (0);
		}
	}
	i = 0;
	while (i < n)
	{
		pthread_mutex_unlock(&philos[i].m_start);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < n)
	{
		pthread_mutex_unlock(&philos[i].m_start);
		i += 2;
	}
	return (1);
}
