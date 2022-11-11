/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:14:44 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 15:40:13 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philos(int n, pid_t *philos)
{
	int	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < n)
		{
			kill(philos[i], SIGKILL);
			++i;
		}
		free(philos);
	}
	sem_unlink("philo_start");
	sem_unlink("philo_end");
	sem_unlink("philo_print");
	sem_unlink("philo_forks");
	sem_unlink("philo_fullness");
	sem_unlink("philo_take");
}

int	finish_simulation(t_table *table, pid_t *philos)
{
	int	n;

	sem_wait(table->sem_end);
	sem_wait(table->sem_end);
	n = table->input.num_of_philos;
	destroy_philos(n, philos);
	return (1);
}
