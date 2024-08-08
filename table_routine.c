/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   waiter.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jschott <jschott@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/10/19 17:39:44 by jschott		   #+#	#+#			 */
/*   Updated: 2023/10/20 08:41:36 by jschott		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

/**
 * Determines if a philosopher has died based on the current time and their time of death.
 * 
 * @param philo A pointer to a `t_philo` structure representing the philosopher to check.
 * @return Returns 1 if the philosopher has died, 0 otherwise.
 */
int	philo_died(t_philo *philo)
{
	if (gettime() - *philo->time_of_death < 0)
		return (0);
	return (1);
}

/**
 * Updates the death count of philosophers at the table.
 * 
 * @param table A pointer to a `t_table` structure representing the dining table.
 * @param phlsphr A pointer to a `t_philo` structure representing the philosopher to check.
 * @return Returns the death count (1 if the philosopher has died, 0 otherwise).
 */
int	update_death_count(t_table *table, t_philo *phlsphr)
{
	int	death_count;

	death_count = 0;
	pthread_mutex_lock(&table->lock);
	pthread_mutex_lock(&phlsphr->lock);
	death_count = philo_died(phlsphr);
	table->deaths = death_count;
	pthread_mutex_unlock(&table->lock);
	pthread_mutex_unlock(&phlsphr->lock);
	if (death_count)
		status_mssg(STATE_DIE, phlsphr);
	return (death_count);
}

/**
 * Checks if a philosopher has been fully fed.
 * 
 * @param phlsphr A pointer to a `t_philo` structure representing the philosopher to check.
 * @return Returns the number of meals left for the philosopher.
 */
int	philo_fed(t_philo *phlsphr)
{
	long int	meals_left;

	pthread_mutex_lock(&phlsphr->lock);
	meals_left = phlsphr->meals;
	pthread_mutex_unlock(&phlsphr->lock);
	return (meals_left);
}

/**
 * Simulates the routine of the dining table, checking for philosopher deaths and meal completion.
 * 
 * This function represents the main loop of the dining table simulation. It periodically checks if any philosopher
 * has died or if all philosophers have been fully fed. The simulation ends when either all philosophers are dead
 * or fully fed.
 * 
 * @param arg A void pointer to a `t_table` structure representing the dining table.
 * @return Always returns 0. This return value is used to comply with the pthreads function signature.
 */
void	*table_routine(void *arg)
{
	int		i;
	int		j;
	t_table	*table;

	table = (t_table *) arg;
	i = 0;
	usleep(900 * table->philo_t2d);
	while (table->deaths == 0)
	{
		j = 0;
		if (update_death_count(table, table->philos[i]) == 0 \
			&& table->philo_meals > 0)
		{
			while (j < table->philo_num && philo_fed(table->philos[j]) <= 0)
				j++;
			if (j == table->philo_num)
				break ;
		}
		i = (i + 1) % table->philo_num;
	}
	return (0);
}
