/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:05:49 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 16:54:01 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if (!init(argc, argv, &table, &philos))
		return (1);
	if (!create_threads(table.input.num_of_philos, philos))
		return (2);
	while (!is_simulation_finished(&table))
		usleep(500);
	if (!finish_simulation(&table, philos))
		return (3);
	return (0);
}
