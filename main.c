/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:49 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/06 21:30:08 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
	{
		free_all(&table);
		printf("%sArgument count error!%s", RED, DEFAULT);
		return (1);
	}	
	if (check_and_parse(&table, argv, argc))
	{
		free_all(&table);
		printf("%sInvalid arguments or parse error!%s", RED, DEFAULT);
		return (1);
	}
	if (run_philosophers(&table))
	{		
		free_all(&table);
		printf("%sExecution error!%s", RED, DEFAULT);
		return (1);
	}
	free_all(&table);
	return (0);
}
