/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ritual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:32:37 by elisa             #+#    #+#             */
/*   Updated: 2023/09/24 18:52:22 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->dead == 0)
	{
		time = actual_time() - philo->table->start_time;
		printf("%ld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->lock);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	write_status("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	write_status("has taken a fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	write_status("is sleeping", philo);
	ft_usleep(philo->table->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->times[philo->id]);
	philo->time_eat = actual_time();
	pthread_mutex_unlock(&philo->table->times[philo->id]);
	write_status("is eating", philo);
	philo->eat = 1;
	ft_usleep(philo->table->eat_time);
	philo->eat = 0;
	philo->eat_count++;
	drop_forks(philo);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (philo->table->dead == 0)
	{
		eat(philo);
		write_status("is thinking", philo);
	}
	return (0);
}
