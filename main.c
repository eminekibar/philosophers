#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
		exit_safe("Argument count error!", EXIT_FAILURE, &table);
	if (check_and_parse(&table, argv, argc))
		exit_safe("Invalid arguments or parse error!", EXIT_FAILURE, &table);
	if (run_philosophers(&table))
		exit_safe("Execution error!", EXIT_FAILURE, &table);
	return (0);
}
