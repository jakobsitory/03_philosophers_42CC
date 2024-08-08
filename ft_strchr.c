/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschott <jschott@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:52 by jschott           #+#    #+#             */
/*   Updated: 2024/08/08 11:46:56 by jschott          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Searches for the first occurrence of a character in a string.
 * 
 * @param s The string to be scanned.
 * @param c The character to search for. It is an `int` which allows for EOF to be passed as a character but is
 *          internally treated as an `unsigned char` for comparison.
 * @return A pointer to the matched character in the string, or `NULL` if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *) &s[i]);
	return (0);
}
