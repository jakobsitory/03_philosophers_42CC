/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:37:08 by jschott           #+#    #+#             */
/*   Updated: 2023/12/11 10:19:10 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_ARGC		1
# define ERR_INPT		2
# define ERR_RNTM		3
# define ERR_THRD		4
# define ERR_FORKS		5
# define ERR_PHLSPHR	6
# define ERR_MTX		7
# define ERR_TMDFF		8

# define STATE_FORK		"has taken a fork\n"
# define STATE_EAT		"is eating\n"
# define STATE_SLEEP	"is sleeping\n"
# define STATE_THINK	"is thinking\n"
# define STATE_DIE		"died \n"

typedef struct s_table {
	long int		start_time;
	long int		philo_num;
	long int		philo_t2d;
	long int		philo_t2e;
	long int		philo_t2s;
	long int		philo_meals;
	int				deaths;
	pthread_mutex_t	lock;
	long int		*philos_t2d;
	struct s_philo	**philos;
}					t_table;

typedef struct s_philo {
	long int		num;
	pthread_mutex_t	lock;
	pthread_mutex_t	*table_lock;
	long int		*t2die;
	long int		*t2eat;
	long int		*t2slp;
	long int		time_of_birth;
	long int		*time_of_death;
	long int		*time_of_start;
	pthread_mutex_t	*forks[2];
	long int		meals;
	int				*deaths_table;
}					t_philo;

int				ft_issign(char c);
char			*ft_strchr(const char *s, int c);
long			ft_atol(const char *str);
void			error_mgmt(int err_cd);
void			status_mssg(char *event, t_philo *philo);
int				table_init(t_table *table, char **argv);
pthread_mutex_t	*fork_init(long num);
int				fork_destroy(pthread_mutex_t *ctlry, long num);
t_philo			**philo_init(long num, t_table *table, pthread_mutex_t *ctlry);
void			philo_destroy(t_philo **phlsphrs, long num);
int				table_set(t_table *table);
int				table_destroy(t_table *table);
void			*table_routine(void *arg);
int				start_eating(t_table *table, t_philo **phlsphrs);
long			gettime(void);
int				philo_fed(t_philo *phlsphr);

// PLAYGROUND
void			print_table(t_table *table);
void			print_philo(t_philo *philo);

#endif