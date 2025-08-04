/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:36 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 20:05:36 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		table->philo[i].id = i;
		table->philo[i].right_fork = i;
		table->philo[i].left_fork = (i + 1) % table->number_of_philosophers;
		table->philo[i].last_eat_time = 0;
		table->philo[i].meal_count = 0;
		table->philo[i].table = table;
	}
	return (0);
}

static int	mutex_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		(table->init_forkmutex_count)++;
	}
	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->philo[i].eating_mutex, NULL))
			return (1);
		(table->init_eatmutex_count)++;
	}
	if (pthread_mutex_init(&table->writing, NULL))
		return (1);
	table->init_writing_mutex = 1;
	if (pthread_mutex_init(&table->die_check, NULL))
		return (1);
	table->init_die_check_mutex = 1;
	return (0);
}

void	init_all(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philo)
		exit_safe("Malloc error!", EXIT_FAILURE, table);
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	if (!table->forks)
		exit_safe("Malloc error!", EXIT_FAILURE, table);
	ft_memset(table->forks, 0, sizeof(pthread_mutex_t)
		* table->number_of_philosophers);
	if (mutex_init(table))
		exit_safe("Mutex error!", EXIT_FAILURE, table);
	philo_init(table);
}
