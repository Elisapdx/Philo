/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:19:51 by elisa             #+#    #+#             */
/*   Updated: 2023/09/24 18:44:25 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/********************LIBRARY********************/

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*******************STRUCTURES******************/

typedef struct s_philo
{
	struct s_table	*table;
	int				eat;
	int				eat_count;
	int				id;
	long int		time_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_table
{
	pthread_t		*tid;
	int				dead;
	int				meals_nb;
	int				finished;
	int				philo_num;
	t_philo			*philos;
	long int		start_time;
	long int		eat_time;
	long int		sleep_time;
	long int		dead_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*times;
}	t_table;

/*******************FONCTIONS*******************/

// init.c
long int	ft_atoi(const char *str);
int			init_table(t_table *table, int ac, char **av);
int			init_philo(t_table *table);
int			init_forks(t_table *table);

// main.c
void		ft_usleep(long int time_in_ms);
void		ft_exit(t_table *table);
void		create_threads(t_table *table);

// ritual.c
void		write_status(char *str, t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eat(t_philo *philo);
void		*routine(void *philo_pointer);

// threads.c
int			exit_time(char *str);
long int	actual_time(void);
int			check_eat(t_table *table);
void		check_death(t_table *table);

// utils.c
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_strcmp(char *s1, char *s2);

#endif