/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:02 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 20:43:58 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop_conditions(t_philo *ph)
{
	int	died;
	int	full;

	pthread_mutex_lock(&ph->table->die_check);
	died = ph->table->dead_flag;
	full = ph->table->full_flag;
	pthread_mutex_unlock(&ph->table->die_check);
	if (!died || !full)
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 1)
		usleep(15000);
	while (1)
	{
		if (check_stop_conditions(ph))
			break ;
		if (eat_meal(ph))
			break ;
		if (check_stop_conditions(ph))
			break ;
		ft_message("is sleeping", ph->table, ph->id);
		ft_wait(ph->table->time_to_sleep, ph->table);
		if (check_stop_conditions(ph))
			break ;
		ft_message("is thinking", ph->table, ph->id);
	}
	return (NULL);
}

int	run_philosophers(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	table->start_time = current_time_ms();
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&(table->philo + i)->philos, NULL,
				routine, table->philo + i))
			return (1);
		pthread_mutex_lock(&table->philo[i].eating_mutex);
		(table->philo + i)->last_eat_time = current_time_ms();
		pthread_mutex_unlock(&table->philo[i].eating_mutex);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table))
		return (1);
	pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_join(table->philo[i].philos, NULL);
	free_all(table);
	return (0);
}
