/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:05:33 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:44:50 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Checks if there have been any deaths at the table.
 * 
 * @param phlsphr A pointer to a `t_philo` structure representing the philosopher.
 * @return Returns the death count. If the count is greater than 0, it indicates that at least one philosopher has died.
 */
int	check_table_deaths(t_philo *phlsphr)
{
	int	death_count;

	death_count = 0;
	pthread_mutex_lock(phlsphr->table_lock);
	death_count = *phlsphr->deaths_table;
	pthread_mutex_unlock(phlsphr->table_lock);
	return (death_count);
}

/**
 * Attempts to take a fork for a philosopher.
 * 
 * @param phlsphr A pointer to a `t_philo` structure representing the philosopher.
 * @param fork A pointer to a `pthread_mutex_t` representing the fork to be taken.
 * @return Returns 1 if the fork was successfully taken, 0 otherwise.
 */
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

/**
 * Simulates a philosopher eating.
 * 
 * @param phlsphr A pointer to a `t_philo` structure representing the philosopher.
 * @return Returns `EXIT_FAILURE` if the philosopher cannot take both forks or `EXIT_SUCCESS` after successfully eating.
 */
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

/**
 * The routine a philosopher follows in the simulation.
 * 
 * This function represents the main routine of a philosopher in the simulation. It initializes the philosopher's time
 * of birth and time of death, then enters a loop where it simulates eating, sleeping, and thinking as long as no
 * philosopher has died. The loop breaks if the philosopher successfully eats and there are no deaths, or if the
 * philosopher is fully fed.
 * 
 * @param ptr A void pointer that is cast to a `t_philo` structure representing the philosopher.
 * @return Always returns 0. This return value is used to comply with the pthreads function signature.
 */
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

/**
 * Starts the eating simulation for all philosophers.
 * 
 * This function creates and starts threads for each philosopher to begin their routine in the simulation. It allocates
 * memory for the threads, creates a thread for each philosopher, and then waits for all threads to complete. If thread
 * creation fails, it calls `error_mgmt` with an error code. After all threads have completed, it frees the allocated
 * memory for the threads.
 * 
 * @param table A pointer to a `t_table` structure representing the dining table.
 * @param phlsphrs A pointer to an array of `t_philo` pointers, each representing a philosopher.
 * @return Returns `EXIT_SUCCESS` after successfully starting and completing the simulation for all philosophers.
 */
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
