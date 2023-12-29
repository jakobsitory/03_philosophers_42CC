/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:05:33 by jschott           #+#    #+#             */
/*   Updated: 2023/12/11 15:25:21 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_table_deaths(t_philo *phlsphr)
{
	int	death_count;

	death_count = 0;
	pthread_mutex_lock(phlsphr->table_lock);
	death_count = *phlsphr->deaths_table;
	pthread_mutex_unlock(phlsphr->table_lock);
	return (death_count);
}

int	take_fork(t_philo *phlsphr, pthread_mutex_t *fork)
{
	if (!fork)
	{
		usleep(1000 * *phlsphr->t2die);
		return (0);
	}
	pthread_mutex_lock(fork);
	if (check_table_deaths(phlsphr))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	status_mssg(STATE_FORK, phlsphr);
	return (1);
}

int	philo_eating(t_philo *phlsphr)
{
	if (!take_fork(phlsphr, phlsphr->forks[0]))
		return (EXIT_FAILURE);
	if (!take_fork(phlsphr, phlsphr->forks[1]))
	{
		pthread_mutex_unlock(phlsphr->forks[0]);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(phlsphr->table_lock);
	pthread_mutex_lock(&phlsphr->lock);
	(*phlsphr->time_of_death) += (*phlsphr->t2die);
	phlsphr->meals--;
	pthread_mutex_unlock(phlsphr->table_lock);
	pthread_mutex_unlock(&phlsphr->lock);
	status_mssg(STATE_EAT, phlsphr);
	usleep(1000 * *phlsphr->t2eat);
	if (phlsphr->forks[0])
		pthread_mutex_unlock(phlsphr->forks[0]);
	if (phlsphr->forks[1])
		pthread_mutex_unlock(phlsphr->forks[1]);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *ptr)
{
	t_philo			*phlsphr;

	phlsphr = (t_philo *) ptr;
	phlsphr->time_of_birth = gettime();
	pthread_mutex_lock(&phlsphr->lock);
	(*phlsphr->time_of_death) = phlsphr->time_of_birth + (*phlsphr->t2die);
	pthread_mutex_unlock(&phlsphr->lock);
	while (!check_table_deaths(phlsphr))
	{
		if (philo_eating(phlsphr))
			break ;
		if (check_table_deaths(phlsphr))
			break ;
		status_mssg(STATE_SLEEP, phlsphr);
		usleep(1000 * *phlsphr->t2slp);
		if (check_table_deaths(phlsphr))
			break ;
		status_mssg(STATE_THINK, phlsphr);
		if (!philo_fed(phlsphr))
			break ;
	}
	return (0);
}

int	start_eating(t_table *table, t_philo **phlsphrs)
{
	pthread_t	*philo_thrd;
	int			i;

	i = -1;
	philo_thrd = (pthread_t *) malloc (table->philo_num * sizeof(pthread_t));
	if (philo_thrd)
	{
		while (++i < table->philo_num)
		{
			if (pthread_create(&philo_thrd[i], NULL, \
								&philo_routine, phlsphrs[i]) != 0)
				error_mgmt(ERR_THRD);
			usleep(1);
		}
		while (--i >= 0)
		{
			if (pthread_join(philo_thrd[i], NULL) != 0)
				error_mgmt(ERR_THRD);
		}
	}
	free(philo_thrd);
	return (EXIT_SUCCESS);
}
