/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnelson <nnelson@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:56:13 by andreys           #+#    #+#             */
/*   Updated: 2022/07/19 13:27:31 by nnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_fullness(t_table *table, int meals_eaten)
{
	if (!is_simulation_finished(table)
		&& meals_eaten == table->input.num_times_to_eat)
	{
		pthread_mutex_lock(&table->m_fullness);
		table->num_full_philos += 1;
		pthread_mutex_unlock(&table->m_fullness);
	}
}

static void	philo_take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (is_simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(fork);
	print_message("has taken a fork", philo);
}

void	philo_eat(t_philo *philo)
{
	philo_take_fork(philo, philo->left);
	philo_take_fork(philo, philo->right);
	if (is_simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(&philo->m_time);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->m_time);
	print_message("is eating", philo);
	ms_sleep(philo->table->input.time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_finished(philo->table))
		return ;
	print_message("is sleeping", philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	ms_sleep(philo->table->input.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (is_simulation_finished(philo->table))
		return ;
	print_message("is thinking", philo);
	usleep(100);
}
