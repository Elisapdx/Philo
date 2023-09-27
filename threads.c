/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:23:43 by elisa             #+#    #+#             */
/*   Updated: 2023/09/27 15:33:00 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_time(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		exit_time("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	check_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->meals_nb < 0)
		return (0);
	while (i < table->philo_num)
	{
		if (table->philos[i].eat_count < table->meals_nb)
			return (0);
		i++;
	}
	return (1);
}

void	check_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->philo_num)
		{
			if (table->philos[i].eat == 0)
			{
				if (actual_time() - table->philos[i].time_eat
					>= table->dead_time)
				{
					write_status("died", &table->philos[i]);
					table->dead = 1;
					return ;
				}
			}
			i++;
		}
		if (check_eat(table))
			break ;
	}
	table->dead = 1;
}
