/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:04:52 by jschott           #+#    #+#             */
/*   Updated: 2023/10/24 13:20:54 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	if (!table)
		exit(printf("there is no table\n"));
	printf("\nTABLE:\nstart: %li\nphilo: %li\nt2die: %li\nt2eat: %li\nt2slp: %li\n\n", \
			table->start_time, \
			table->philo_num, table->philo_t2d, \
			table->philo_t2e, table->philo_t2s);
}

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
