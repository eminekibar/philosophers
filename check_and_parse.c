#include "philo.h"

static void one_philo(t_table *table)
{
	long long start_time;
		
	start_time = current_time_ms();
	printf("%s%d%s", RED, 0, DEFAULT);
	printf("%s %d %s", GREEN, 1, DEFAULT);
	printf("%s\n", "has taken a fork");
	usleep(table->time_to_die * 1000);
	printf("%s%lld%s", RED, (current_time_ms() - start_time), DEFAULT);
	printf("%s %d %s", GREEN, 1, DEFAULT);
	printf("%s\n", "is died");
}

static int	check_args(t_table *table, int argc)
{
	if (table->number_of_philosophers < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (1);
	if (argc == 6)
		if (table->number_of_times_each_philosopher_must_eat < 0)
			return (1);
	if (table->number_of_philosophers == 1)
	{
		one_philo(table);
		exit_safe("", EXIT_SUCCESS);
	}
	return (0);
}

int	check_and_parse(t_table *table, char **argv, int argc)
{
	table->number_of_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	table->dead_flag = 1;
	table->full_flag = 1;
	table->init_forkmutex_count = 0;
    table->init_eatmutex_count = 0;
	if (check_args(table, argc))
		exit_safe("Invalid arguments!", EXIT_FAILURE);
	init_all(table);
	return (0);
}
