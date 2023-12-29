/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:22:29 by jschott           #+#    #+#             */
/*   Updated: 2023/12/11 15:27:39 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
