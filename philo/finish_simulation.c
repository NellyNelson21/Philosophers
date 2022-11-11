/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:58:49 by andreys           #+#    #+#             */
/*   Updated: 2022/07/13 19:59:27 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_in_cycle(int n, t_table *table, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		pthread_mutex_destroy(&philos[i].m_start);
		pthread_mutex_destroy(&philos[i].m_time);
		pthread_mutex_destroy(table->m_forks + i);
		pthread_detach(philos[i].thread);
	}
}

int	finish_simulation(t_table *table, t_philo *philos)
{
	int	n;

	n = table->input.num_of_philos;
	destroy_in_cycle(n, table, philos);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_fullness);
	free(philos);
	free(table->m_forks);
	return (1);
}
