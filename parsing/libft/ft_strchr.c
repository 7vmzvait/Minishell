/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:22:04 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 01:26:38 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cs;
	char	cc;

	i = 0;
	cs = (char *)s;
	cc = (char)c;
	while (cs[i])
	{
		if (cs[i] == cc)
		{
			return ((char *)cs + i);
		}
		i++;
	}
	if (cc == '\0')
		return ((char *)cs + i);
	return (NULL);
}
