#include "philo.h"

static int	check_death(t_table *table)
{
	int i;
    long last_eat;

    last_eat = 0;
    i = -1;
	while (++i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philo[i].eating_mutex);
		last_eat = table->philo[i].last_eat_time;
		pthread_mutex_unlock(&table->philo[i].eating_mutex);
		if ((current_time_ms() - last_eat) > table->time_to_die)
		{
			philo_msg("is died", table, table->philo[i].id);
			pthread_mutex_lock(&table->die_check);
			table->dead_flag = 0;
			pthread_mutex_unlock(&table->die_check);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

static int	is_philo_full(t_philo *philo, int max_eat)
{
	int	meals;

	pthread_mutex_lock(&philo->eating_mutex);
	meals = philo->meal_count;
	pthread_mutex_unlock(&philo->eating_mutex);
	if (meals < max_eat)
		return (0);
	return (1);
}

static int	check_all_full(t_table *table)
{
	int all_full;
	int i;

	all_full = 1;
	i = -1;
	if (table->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (++i < table->number_of_philosophers)
	{
		if (!is_philo_full(&table->philo[i], table->number_of_times_each_philosopher_must_eat))
		{
			all_full = 0;
			break;
		}
	}
	if (all_full)
	{
		pthread_mutex_lock(&table->die_check);
		table->full_flag = 0;
		pthread_mutex_unlock(&table->die_check);
		return (1);
	}
	return (0);
}

void *monitor(void *t)
{
	t_table *table;

    table = (t_table *)t;
	while (1)
	{
		pthread_mutex_lock(&table->die_check);
		if (!table->full_flag || !table->dead_flag)
		{
			pthread_mutex_unlock(&table->die_check);
			break;
		}
		pthread_mutex_unlock(&table->die_check);
		if (check_death(table))
			break;
		if (check_all_full(table))
			break;
	}
	return NULL;
}
