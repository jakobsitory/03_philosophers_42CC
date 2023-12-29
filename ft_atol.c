/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:33:53 by jschott           #+#    #+#             */
/*   Updated: 2023/10/24 13:34:42 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_issign(char c)
{
	if (c == '+')
		return (1);
	else if (c == '-')
		return (-1);
	else
		return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (('0' <= c) && (c <= '9'))
		return (1);
	else
		return (0);
}

long	ft_toli(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) != 0)
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb);
}

long	ft_atol(const char *str)
{
	long int	i;
	long int	s;

	i = 0;
	s = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issign(str[i]))
	{
		s = (long) ft_issign(str[i]);
		i++;
	}
	if (ft_isdigit(str[i]))
		return (s * ft_toli(&str[i]));
	else
		return (0);
}
