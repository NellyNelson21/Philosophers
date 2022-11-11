/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:07:54 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 16:54:49 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *message, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%s", message);
	pthread_mutex_unlock(mutex);
}

void	print_message(char *message, t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->m_print);
	if (is_simulation_finished(table))
		return ;
	printf("%lu %i %s\n", get_time_ms() - table->time_start, philo->id, message);
	pthread_mutex_unlock(&table->m_print);
}
