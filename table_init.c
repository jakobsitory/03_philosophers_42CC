/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:36:27 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:42:30 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Destroys a dining table structure and frees allocated resources.
 * 
 * @param table A pointer to the `t_table` structure to be destroyed.
 * @return Returns `EXIT_SUCCESS` on successful cleanup and `EXIT_FAILURE` if the `table` pointer is NULL.
 */
int	table_destroy(t_table *table)
{
	if (!table)
		return (EXIT_FAILURE);
	free (table->philos_t2d);
	philo_destroy(table->philos, table->philo_num);
	free (table);
	return (EXIT_SUCCESS);
}

/**
 * Initializes a dining table structure with parameters provided via command line arguments.
 * 
 * This function sets up a `t_table` structure using command line arguments. It checks for the validity of the `table`
 * and `argv` pointers. If either is NULL, it returns `ERR_INPT` to indicate an input error. The function then
 * initializes the dining table's parameters such as the number of philosophers, time to die, time to eat, time to
 * sleep, and optionally, the number of meals each philosopher must eat before the simulation can end.
 * 
 * If any of the parameters are invalid (e.g., negative values or a zero philosopher count when an optional meals
 * parameter is provided), it frees the allocated `table` and calls `error_mgmt` with `ERR_INPT`.
 * 
 * The function also initializes a mutex for synchronizing access to shared resources and allocates memory for an
 * array to keep track of each philosopher's time to die.
 * 
 * @param table A pointer to the `t_table` structure to be initialized.
 * @param argv An array of strings containing the command line arguments.
 * @return Returns `EXIT_SUCCESS` on successful initialization or `EXIT_FAILURE`/`ERR_INPT` on error.
 */
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
