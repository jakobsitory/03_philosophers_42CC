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

int	philo_died(t_philo *philo)
{
	if (gettime() - *philo->time_of_death < 0)
		return (0);
	return (1);
}

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

int	philo_fed(t_philo *phlsphr)
{
	long int	meals_left;

	pthread_mutex_lock(&phlsphr->lock);
	meals_left = phlsphr->meals;
	pthread_mutex_unlock(&phlsphr->lock);
	return (meals_left);
}

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
