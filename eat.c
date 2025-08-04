/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:17 by ekibar            #+#    #+#             */
/*   Updated: 2025/08/04 20:05:17 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right = philo->right_fork;
	if (left < right)
	{
		pthread_mutex_lock(&philo->table->forks[left]);
		ft_message("has taken a fork", philo->table, philo->id);
		pthread_mutex_lock(&philo->table->forks[right]);
		ft_message("has taken a fork", philo->table, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[right]);
		ft_message("has taken a fork", philo->table, philo->id);
		pthread_mutex_lock(&philo->table->forks[left]);
		ft_message("has taken a fork", philo->table, philo->id);
	}
}

static void	eat_action(t_philo *philo)
{
	ft_message("is eating", philo->table, philo->id);
	pthread_mutex_lock(&philo->eating_mutex);
	philo->last_eat_time = current_time_ms();
	pthread_mutex_unlock(&philo->eating_mutex);
	ft_wait(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->eating_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->eating_mutex);
}

static void	unlock_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right = philo->right_fork;
	if (left < right)
	{
		pthread_mutex_unlock(&philo->table->forks[right]);
		pthread_mutex_unlock(&philo->table->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks[left]);
		pthread_mutex_unlock(&philo->table->forks[right]);
	}
}

int	eat_meal(t_philo *philo)
{
	lock_forks(philo);
	eat_action(philo);
	unlock_forks(philo);
	return (0);
}
