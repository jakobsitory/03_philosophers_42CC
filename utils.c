/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:04:52 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:40:50 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Prints the details of the dining table to standard output.
 * 
 * Note: This function uses `exit` to terminate the program if the `table` pointer is NULL, indicating a critical
 * error where the simulation cannot proceed without a valid table configuration.
 * 
 * @param table A pointer to a `t_table` structure containing the dining table's details.
 * @return This function does not return a value.
 */
void	print_table(t_table *table)
{
	if (!table)
		exit(printf("there is no table\n"));
	printf("\nTABLE:\nstart: %li\nphilo: %li\nt2die: %li\nt2eat: %li\nt2slp: %li\n\n", \
			table->start_time, \
			table->philo_num, table->philo_t2d, \
			table->philo_t2e, table->philo_t2s);
}

/**
 * Prints the details of a philosopher to standard output.
 * 
 * @param phlsphr A pointer to a `t_philo` structure containing a philosopher's details.
 * @return This function does not return a value.
 */
void	print_philo(t_philo *phlsphr)
{
	printf("PHILOSOPHER\n");
	printf("num:\t%li\nmeals:\t%li\nt2die:\t%li\nt2eat:\t%li\nt2slp:\t%li\ndthct:\t%i\n", \
			phlsphr->num, phlsphr->meals, (*phlsphr->t2die), \
			(*phlsphr->t2eat), (*phlsphr->t2slp), (*phlsphr->deaths_table));
	printf("birth:\t%li\n", \
			phlsphr->time_of_birth);
	printf("start:\t%li\n", \
			(*phlsphr->time_of_start));
	printf("death:\t%li\n", \
			(*phlsphr->time_of_death));
	printf("forks:\n\t%p\n\t%p\n\n", phlsphr->forks[0], phlsphr->forks[1]);
}
