/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:02:54 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 15:03:40 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_take_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	print_message("has taken a fork", philo);
}

void	check_fullness(t_table *table, int meals_eaten)
{
	if (meals_eaten == table->input.num_times_to_eat)
		sem_post(table->sem_fullness);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem_take);
	philo_take_fork(philo);
	philo_take_fork(philo);
	sem_post(philo->sem_take);
	sem_wait(philo->sem_time);
	philo->last_meal_time = get_time_ms();
	sem_post(philo->sem_time);
	print_message("is eating", philo);
	ms_sleep(philo->table->input.time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	ms_sleep(philo->table->input.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
	usleep(100);
}
