/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 20:06:26 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_ms(void)
{
	struct timeval	t_timeval;

	gettimeofday(&t_timeval, NULL);
	return ((t_timeval.tv_sec * 1000) + (t_timeval.tv_usec / 1000));
}

void	ft_wait(long long wait_time, t_table *table)
{
	long long	start;

	start = current_time_ms();
	while (1)
	{
		pthread_mutex_lock(&table->die_check);
		if (!table->dead_flag)
		{
			pthread_mutex_unlock(&table->die_check);
			break ;
		}
		pthread_mutex_unlock(&table->die_check);
		if (current_time_ms() - start >= wait_time)
			break ;
		usleep(50);
	}
}
