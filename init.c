/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:13:13 by elisa             #+#    #+#             */
/*   Updated: 2023/09/27 15:04:03 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	int			a;
	long int	b;
	long int	i;

	a = 1;
	b = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-')
	{
		a *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		b = b + (str[i] - 48);
		if (!(str[i + 1] < '0' || str[i + 1] > '9'))
			b = b * 10;
		i++;
	}
	return (a * b);
}

int	init_table(t_table *table, int ac, char **av)
{
	table->dead = 0;
	table->philo_num = ft_atoi(av[1]);
	if (table->philo_num == 0)
	{
		printf("Error args\n");
		return (0);
	}
	table->dead_time = (long int) ft_atoi(av[2]);
	table->eat_time = (long int) ft_atoi(av[3]);
	table->sleep_time = (long int) ft_atoi(av[4]);
	if (ac == 6)
		table->meals_nb = ft_atoi(av[5]);
	else
		table->meals_nb = -1;
	if (table->philo_num <= 0 || table->philo_num > 200 || table->dead_time < 0
		|| table->eat_time < 0 || table->sleep_time < 0)
		return (printf("Error args\n"));
	pthread_mutex_init(&table->lock, NULL);
	return (1);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof (t_philo) * (table->philo_num));
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_times = 0;
		table->philos[i].l_fork = malloc(sizeof (pthread_mutex_t) * 1);
		table->philos[i].table = table;
		table->philos[i].time_eat = actual_time();
		i++;
	}
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_num != 1)
	{
		while (i < table->philo_num)
		{
			pthread_mutex_init(table->philos[i].l_fork, NULL);
			if (i + 1 == table->philo_num)
				table->philos[i].r_fork = table->philos[0].l_fork;
			else
				table->philos[i].r_fork = table->philos[i + 1].l_fork;
			i++;
		}
	}
	else
	{
		pthread_mutex_init(table->philos[0].l_fork, NULL);
		table->philos[0].r_fork = table->philos[0].l_fork;
	}
	return (1);
}
