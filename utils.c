#include "philo.h"

void	exit_safe(char *str, int exit_code, t_table *table)
{
        printf("%s%s%s", RED, str, DEFAULT);
        free_all(table);
        exit(exit_code);
}

void     free_all(t_table *table)
{
        int     i;

        i = -1;
        if(table->forks)
        {
                while (++i < table->init_forkmutex_count)
                        pthread_mutex_destroy(&table->forks[i]);
        }
        i = -1;
        if(table->philo)
        {
                while (++i < table->init_eatmutex_count)
                        pthread_mutex_destroy(&table->philo[i].eating_mutex);
        }
        if(table->init_writing_mutex == 1)
                pthread_mutex_destroy(&table->writing);
        if(table->init_diecheck_mutex == 1)
                pthread_mutex_destroy(&table->die_check);
        if(table->philo)
                free(table->philo);
        if(table->forks)
                free(table->forks);
}

void	philo_msg(char *str, t_table *table, int philo_id)
{
        int flag;
        
        pthread_mutex_lock(&table->die_check);
        flag = table->dead_flag;
        pthread_mutex_unlock(&table->die_check);
        if (flag)
	{
                pthread_mutex_lock(&table->writing);
		printf("%s%lld%s", RED, (current_time_ms() - table->start_time), DEFAULT);
		printf("%s %d %s", GREEN, philo_id + 1, DEFAULT);
		printf("%s\n", str);
                pthread_mutex_unlock(&table->writing);
	}
}
