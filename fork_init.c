/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:05 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:39:28 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * Destroys an array of pthread mutexes and frees the allocated memory.
 * 
 * @param ctlry A pointer to the first mutex in the array to be destroyed.
 * @param num The number of mutexes in the array.
 * 
 * @return 0 on successful destruction and memory deallocation, -1 if the `ctlry` pointer is NULL.
 */
int	fork_destroy(pthread_mutex_t *ctlry, long num)
{
	int				i;
	pthread_mutex_t	*tmp;

	i = -1;
	tmp = ctlry;
	if (!tmp)
		return (-1);
	while (++i < num)
		pthread_mutex_destroy(&tmp[i]);
	free (ctlry);
	return (0);
}

/**
 * Initializes and destroys an array of pthread mutexes.
 * 
 * @param num The number of mutexes to initialize. This value should be greater than 0.
 * 
 * @return A pointer to the initialized array of pthread mutexes. If memory allocation fails, the program handles the
 * error through `error_mgmt` and may not return.
 */
pthread_mutex_t	*fork_init(long num)
{
	int				i;
	pthread_mutex_t	*ctlry;

	i = 0;
	if (num <= 0)
		error_mgmt (ERR_FORKS);
	ctlry = (pthread_mutex_t *) malloc (num * sizeof(pthread_mutex_t));
	if (!ctlry)
		error_mgmt(ERR_MTX);
	while (i < num)
		pthread_mutex_init(&ctlry[i++], 0);
	return (ctlry);
}
