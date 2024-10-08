/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:45:11 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:43:18 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Handles error messages based on error codes and exits the program.
 * 
 * @param err_cd The error code indicating the type of error encountered.
 * @return This function does not return a value because it calls `exit` with the error code.
 */
void	error_mgmt(int err_cd)
{
	if (err_cd == ERR_ARGC)
		printf("wrong number of arguments\n");
	else if (err_cd == ERR_INPT)
		printf("input error\n");
	else if (err_cd == ERR_RNTM)
		printf("runtime error\n");
	else if (err_cd == ERR_THRD)
		printf("couldn't create thread\n");
	else if (err_cd == ERR_FORKS)
		printf("couldn't create forks\n");
	else if (err_cd == ERR_PHLSPHR)
		printf("couldn't create philosopher\n");
	else if (err_cd == ERR_MTX)
		printf("couldn't create mutexes\n");
	else if (err_cd == ERR_TMDFF)
		printf("couldn't calc timediff\n");
	else
		printf("unspecified error %i\n", err_cd);
	exit (err_cd);
}

/**
 * Prints a status message for a philosopher's action.
 * 
 * @param event A string describing the philosopher's current event or action.
 * @param philo A pointer to a `t_philo` structure representing the philosopher.
 * @return This function does not return a value.
 */
void	status_mssg(char *event, t_philo *philo)
{
	long			time;

	pthread_mutex_lock(philo->table_lock);
	pthread_mutex_lock(&philo->lock);
	time = gettime() - *philo->time_of_start;
	printf("%6li %4li %s", time, philo->num, event);
	pthread_mutex_unlock(philo->table_lock);
	pthread_mutex_unlock(&philo->lock);
}
