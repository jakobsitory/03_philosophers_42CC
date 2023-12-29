/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:05 by jschott           #+#    #+#             */
/*   Updated: 2023/12/06 17:19:30 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
