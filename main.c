/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:46:17 by elisa             #+#    #+#             */
/*   Updated: 2023/09/24 19:30:42 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start;

	start = actual_time();
	while ((actual_time() - start) < time_in_ms)
		usleep(time_in_ms * 10);
}

void	ft_exit(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(table->philos[i].l_fork);
		free(table->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&table->lock);
	free(table->philos);
	free(table->tid);
}

static int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		if (ft_strlen(av[i]) > 9 && ft_atoi(av[i]) == -1)
			return (0);
	}
	return (1);
}

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = actual_time();
	table->tid = malloc(sizeof(pthread_t) * table->philo_num);
	while (i < table->philo_num)
	{
		pthread_create(&table->tid[i], NULL, routine, &table->philos[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (!check_arg(ac, av))
		{
			printf("Error args\n");
			return (1);
		}
		if (!init_table(&table, ac, av))
			return (0);
		init_philo(&table);
		init_forks(&table);
		create_threads(&table);
		check_death(&table);
		ft_exit(&table);
	}
	else
	{
		printf("usage: <number of philosophers> <Time to die> <Time to eat>");
		printf(" <Time to sleep> <Nullable number of eat>\n");
	}
	return (0);
}
