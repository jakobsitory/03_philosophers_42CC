/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:22:29 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:45:35 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Destroys philosopher structures and frees allocated resources.
 * 
 * @param phlsphrs A pointer to an array of philosopher structures.
 * @param num The number of philosophers in the array.
 */
void	philo_destroy(t_philo **phlsphrs, long num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		pthread_mutex_destroy(&phlsphrs[i]->lock);
		free (phlsphrs[i]);
	}
	free (phlsphrs);
}

/**
 * Creates and initializes a philosopher structure.
 * 
 * @param num The philosopher's number (position at the table).
 * @param table A pointer to the shared table structure.
 * @param ctlry An array of mutexes representing the forks.
 * @return A pointer to the newly created philosopher structure.
 */

t_philo	*create_philo(long num, t_table *table, pthread_mutex_t *ctlry)
{
	t_philo			*phlsphr;

	phlsphr = (t_philo *) malloc (sizeof(t_philo));
	phlsphr->num = num + 1;
	pthread_mutex_init(&phlsphr->lock, 0);
	phlsphr->table_lock = &table->lock;
	phlsphr->forks[(num + 2) % 2] = &ctlry[(num + 1) % table->philo_num];
	if (table->philo_num > 1)
		phlsphr->forks[phlsphr->num % 2] = &ctlry[num];
	else
		phlsphr->forks[phlsphr->num % 2] = 0;
	phlsphr->meals = table->philo_meals;
	phlsphr->t2die = &table->philo_t2d;
	phlsphr->t2eat = &table->philo_t2e;
	phlsphr->t2slp = &table->philo_t2s;
	phlsphr->deaths_table = &table->deaths;
	phlsphr->time_of_start = &table->start_time;
	phlsphr->time_of_death = &table->philos_t2d[num];
	(*phlsphr->time_of_death) = (*phlsphr->t2die) + gettime();
	return (phlsphr);
}

/**
 * Initializes an array of philosopher structures.
 * 
 * @param num The number of philosophers to initialize.
 * @param table A pointer to the shared table structure.
 * @param ctlry An array of mutexes representing the forks.
 * @return A pointer to the array of philosopher structures.
 */
t_philo	**philo_init(long num, t_table *table, pthread_mutex_t *ctlry)
{
	t_philo		**phlsphrs;
	int			i;

	i = -1;
	phlsphrs = (t_philo **) malloc ((table->philo_num) * sizeof(t_philo));
	if (!phlsphrs)
	{
		free (table);
		error_mgmt(ERR_PHLSPHR);
	}
	while (++i < num)
		phlsphrs[i] = create_philo(i, table, ctlry);
	table->philos = phlsphrs;
	return (phlsphrs);
}
