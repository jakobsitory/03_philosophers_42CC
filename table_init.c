/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:36:27 by jschott           #+#    #+#             */
/*   Updated: 2023/12/11 14:45:37 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_destroy(t_table *table)
{
	if (!table)
		return (EXIT_FAILURE);
	free (table->philos_t2d);
	philo_destroy(table->philos, table->philo_num);
	free (table);
	return (EXIT_SUCCESS);
}

int	table_init(t_table *table, char **argv)
{
	if (!table || !argv)
		return (ERR_INPT);
	table->philo_num = ft_atol(argv[0]);
	table->philo_t2d = ft_atol(argv[1]);
	table->philo_t2e = ft_atol(argv[2]);
	table->philo_t2s = ft_atol(argv[3]);
	table->philo_meals = 0;
	table->deaths = 0;
	if (argv[4] && ft_atol(argv[4]) != 0)
		table->philo_meals = ft_atol(argv[4]);
	else if (table->philo_num == 0 || argv[4])
		return (EXIT_FAILURE);
	if (table->philo_num < 0 || table->philo_t2d < 0 || \
		table->philo_t2e < 0 || table->philo_t2s < 0 || table->philo_meals < 0)
	{
		free (table);
		error_mgmt (ERR_INPT);
	}
	table->start_time = gettime();
	pthread_mutex_init(&table->lock, 0);
	table->philos_t2d = (long *) malloc (table->philo_num * sizeof(long int));
	return (EXIT_SUCCESS);
}
