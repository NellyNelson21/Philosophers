/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:44:51 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 16:06:47 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*watcher_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		n;

	table = (t_table *)arg;
	n = table->input.num_of_philos;
	i = 0;
	while (i < n)
	{
		sem_wait(table->sem_fullness);
		++i;
	}
	i = 0;
	while (i < n)
	{
		sem_wait(table->sem_fullness);
		++i;
	}
	sem_wait(table->sem_print);
	sem_post(table->sem_end);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pid_t		*pids;
	pthread_t	watcher;

	if (!init(argc, argv, &table, &pids))
	{
		destroy_philos(table.input.num_of_philos, pids);
		return (1);
	}
	if (table.input.num_times_to_eat != -1)
	{
		if (pthread_create(&watcher, NULL, watcher_routine, &table))
		{
			destroy_philos(table.input.num_of_philos, pids);
			return (2);
		}
		pthread_detach(watcher);
	}
	if (!finish_simulation(&table, pids))
		return (3);
	return (0);
}
