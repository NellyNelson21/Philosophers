/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:09:08 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 15:09:22 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	size_t	timestamp;

	timestamp = get_time_ms() - philo->table->time_start;
	sem_wait(philo->sem_print);
	printf("%lu %d %s\n", timestamp, philo->id, str);
	sem_post(philo->sem_print);
}
