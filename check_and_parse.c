/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:27 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/06 22:09:37 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_table *table, int argc)
{
	if (table->number_of_philosophers < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (1);
	if (argc == 6)
		if (table->number_of_times_each_philosopher_must_eat < 1)
			return (1);
	return (0);
}

int	check_and_parse(t_table *table, char **argv, int argc)
{
	table->number_of_philosophers = ft_atol(argv[1], table);
	table->time_to_die = ft_atol(argv[2], table);
	table->time_to_eat = ft_atol(argv[3], table);
	table->time_to_sleep = ft_atol(argv[4], table);
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_atol(argv[5],
				table);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	if (table->error_flag)
		return (1);
	table->dead_flag = 1;
	table->full_flag = 1;
	table->error_flag = 0;
	table->init_forkmutex_count = 0;
	table->init_eatmutex_count = 0;
	table->init_writing_mutex = 0;
	table->init_die_check_mutex = 0;
	if (check_args(table, argc))
		return (1);
	if (init_all(table))
		return (1);
	return (0);
}
