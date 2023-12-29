/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:44:32 by jschott           #+#    #+#             */
/*   Updated: 2023/12/11 14:44:00 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_str(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			while ((ft_issign(argv[i][j])))
				j++;
			while (argv[i][j] != '\0' && ft_strchr("0123456789", argv[i][j]))
				j++;
			if (argv[i][j] != '\0')
				return (0);
		}
		i++;
	}
	return (i);
}

int	table_set(t_table *table)
{
	pthread_t	*table_thrd;
	t_philo		**phlsphrs;

	phlsphrs = table->philos;
	table_thrd = (pthread_t *) malloc (sizeof(pthread_t));
	if (table_thrd)
	{
		if (pthread_create(table_thrd, NULL, &table_routine, table))
			error_mgmt(ERR_THRD);
		start_eating (table, phlsphrs);
		if (pthread_join(*table_thrd, NULL) != 0)
			error_mgmt(ERR_THRD);
	}
	free (table_thrd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table			*table;
	pthread_mutex_t	*ctlry;

	if (argc < 5 || argc > 6)
		error_mgmt(ERR_ARGC);
	if (!num_str(&argv[1]))
		error_mgmt(ERR_INPT);
	table = (t_table *) malloc(sizeof(t_table));
	if (table_init(table, &argv[1]) == EXIT_FAILURE)
	{
		free (table);
		return (EXIT_FAILURE);
	}
	ctlry = fork_init(table->philo_num);
	if (!ctlry)
		error_mgmt(ERR_INPT);
	table->philos = philo_init(table->philo_num, table, ctlry);
	if (!table->philos)
		error_mgmt(ERR_INPT);
	table_set(table);
	table_destroy (table);
	free (ctlry);
	return (EXIT_SUCCESS);
}
