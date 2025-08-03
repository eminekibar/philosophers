#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		exit_safe("Argument count error!", EXIT_FAILURE);
	if (check_and_parse(&table, argv, argc))
		exit_safe("Invalid arguments or parse error!", EXIT_FAILURE);
	if (run_philosophers(&table))
		exit_safe("Execution error!", EXIT_FAILURE);
	return (0);
}
