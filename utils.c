#include "philo.h"

void	exit_safe(char *str, int exit_code)
{
        printf("%s%s%s", RED, str, DEFAULT);
        exit(exit_code);
}

void     free_all(t_table *table)
{
        int     i;

        i = -1;
        while (++i < table->init_forkmutex_count)
                pthread_mutex_destroy(&table->forks[i]);
        i = -1;
        while (++i < table->init_eatmutex_count)
                pthread_mutex_destroy(&table->philo[i].eating_mutex);
        pthread_mutex_destroy(&table->writing);
        pthread_mutex_destroy(&table->die_check);
        free(table->philo);
        free(table->forks);
}

void	philo_msg(char *str, t_table *table, int philo_id)
{
	pthread_mutex_lock(&table->writing);
        if (table->dead_flag)
	{
		printf("%s%lld%s", RED, (current_time_ms() - table->start_time), DEFAULT);
		printf("%s %d %s", GREEN, philo_id + 1, DEFAULT);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&table->writing);
}
