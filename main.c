/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:49 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 21:31:34 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	argv = argv_split(&argc, argv);
	if (!argv)
		return (0);
	ft_memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
		exit_safe("Argument count error!", EXIT_FAILURE, &table);
	if (check_and_parse(&table, argv, argc))
		exit_safe("Invalid arguments or parse error!", EXIT_FAILURE, &table);
	if (run_philosophers(&table))
		exit_safe("Execution error!", EXIT_FAILURE, &table);
	return (0);
}
