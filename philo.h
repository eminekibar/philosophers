#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define DEFAULT "\033[0m"

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				meal_count;
	long long		last_eat_time;
	pthread_mutex_t	eating_mutex;
	pthread_t		philos;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead_flag;
	int				full_flag;
	int				i;
	int				init_eatmutex_count;
	int				init_forkmutex_count;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	die_check;
	t_philo			*philo;
}					t_table;

int		check_and_parse(t_table *table, char **str, int argc);
int 	eat_meal(t_philo *philo);
int		run_philosophers(t_table *table);
long	ft_atol(char *str);
long long	current_time_ms(void);
char	*is_valid(char *str);
void	*monitor(void *t);
void	*ft_memset(void *b, int c, size_t len);
void     free_all(t_table *table);
void	exit_safe(char *str, int exit_code);
void	philo_msg(char *str, t_table *table, int id);
void	ft_wait(long long wait_time, t_table *table);
void	init_all(t_table *table);

#endif
