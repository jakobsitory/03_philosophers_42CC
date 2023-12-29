/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:58:59 by jschott           #+#    #+#             */
/*   Updated: 2023/10/24 14:21:54 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
