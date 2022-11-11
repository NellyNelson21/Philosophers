/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:02:06 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 17:33:41 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_input(int argc, char **argv, t_input *input)
{
	if (argc != 5 && argc != 6)
	{
		printf("ERROR: incorrect number of arguments!\n");
		return (0);
	}
	input->num_of_philos = process_arg(argv[1]);
	input->time_to_die = process_arg(argv[2]);
	input->time_to_eat = process_arg(argv[3]);
	input->time_to_sleep = process_arg(argv[4]);
	if (argc == 6)
		input->num_times_to_eat = process_arg(argv[5]);
	else
		input->num_times_to_eat = -1;
	if (input->num_of_philos * input->time_to_die * input->time_to_eat
		* input->time_to_sleep * input->num_times_to_eat == 0)
	{
		printf("ERROR: none of argument can be 0!\n");
		return (0);
	}
	return (1);
}

static int	init_table(t_table *table)
{
	int				n;
	pthread_mutex_t	*forks;

	n = table->input.num_of_philos;
	forks = malloc(n * sizeof(*forks));
	if (!forks)
		return (0);
	while (n > 0)
	{
		if (pthread_mutex_init(&forks[--n], NULL) != 0)
			return (0);
	}
	table->m_forks = forks;
	if (pthread_mutex_init(&table->m_print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->m_fullness, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philo(t_philo **philos, t_table *table)
{
	int			n;
	int			i;
	t_philo		*philofers;

	n = table->input.num_of_philos;
	philofers = malloc(n * sizeof(*philofers));
	if (!philofers)
		return (0);
	i = 0;
	while (i < n)
	{
		philofers[i].id = i + 1;
		philofers[i].left = &table->m_forks[i];
		philofers[i].right = &table->m_forks[(1 + i) % n];
		if (pthread_mutex_init(&philofers[i].m_start, NULL)
			|| pthread_mutex_init(&philofers[i].m_time, NULL))
			return (0);
		philofers[i].table = table;
		pthread_mutex_lock(&philofers[i].m_start);
		i++;
	}
	*philos = philofers;
	return (1);
}

int	init(int argc, char **argv, t_table *table, t_philo **philos)
{
	if (!init_input(argc, argv, &table->input))
		return (0);
	if (!init_table(table))
		return (0);
	if (!init_philo(philos, table))
		return (0);
	table->num_full_philos = 0;
	table->ok = 1;
	table->time_start = get_time_ms();
	return (1);
}
