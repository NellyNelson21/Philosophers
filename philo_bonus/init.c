/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:08:21 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 18:45:47 by andreys          ###   ########.fr       */
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

int	semaphore_create(const char *name, int value, sem_t **sem)
{
	if (value == 0)
		*sem = sem_open(name, 0);
	else
	{
		sem_unlink(name);
		*sem = sem_open(name, O_CREAT | O_EXCL, 0700, value);
	}
	return (*sem != SEM_FAILED);
}

static int	init_semaphores(t_table *table)
{
	int	n;

	n = table->input.num_of_philos;
	table->sem_forks = SEM_FAILED;
	table->sem_fullness = SEM_FAILED;
	table->sem_print = SEM_FAILED;
	if (!semaphore_create("philo_forks", n, &table->sem_forks)
		|| !semaphore_create("philo_fullness", n, &table->sem_fullness)
		|| !semaphore_create("philo_print", 1, &table->sem_print)
		|| !semaphore_create("philo_start", n, &table->sem_start)
		|| !semaphore_create("philo_end", 1, &table->sem_end)
		|| !semaphore_create("philo_take", 1, &table->sem_take))
		return (0);
	return (1);
}

static int	init_philos(int n, t_table *table, pid_t *pids)
{
	int		i;
	size_t	t_start;
	t_philo	philo;

	t_start = get_time_ms();
	table->time_start = t_start;
	i = -1;
	while (++i < n)
		sem_wait(table->sem_start);
	i = -1;
	while (++i < n)
	{
		philo.table = table;
		philo.id = i + 1;
		philo.time_start = t_start;
		pids[i] = start_simulation(&philo);
		if (pids[i] == -1)
			return (0);
	}
	i = -1;
	while (++i < n)
		sem_post(table->sem_start);
	return (1);
}

int	init(int argc, char **argv, t_table *table, pid_t **pids)
{
	*pids = NULL;
	if (!init_input(argc, argv, &table->input))
		return (0);
	if (!init_semaphores(table))
		return (0);
	*pids = malloc(table->input.num_of_philos * sizeof **pids);
	if (*pids == NULL)
		return (0);
	if (!init_philos(table->input.num_of_philos, table, *pids))
		return (0);
	return (1);
}
