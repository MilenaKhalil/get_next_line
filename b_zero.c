/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 13:47:56 by mikhalil      #+#    #+#                 */
/*   Updated: 2022/11/23 18:16:57 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	b_zero(void *s, size_t n)
{
	size_t	i;
	char	*t;

	t = (char *)s;
	i = 0;
	while (i < n)
	{
		t[i] = 0;
		i++;
	}
}
