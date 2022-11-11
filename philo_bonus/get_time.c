/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreys <andreys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:36:19 by andreys           #+#    #+#             */
/*   Updated: 2022/07/18 17:26:57 by andreys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	time_val;
	size_t			ms;

	gettimeofday(&time_val, NULL);
	ms = (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
	return (ms);
}

void	ms_sleep(int t_ms)
{
	size_t	start;
	size_t	end;

	start = get_time_ms();
	end = start + t_ms;
	while (get_time_ms() < end)
	{
		usleep(500);
	}
}
