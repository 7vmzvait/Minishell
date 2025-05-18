/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:33:41 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/21 16:09:34 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	if (c == '\0')
		return ((char *)s + index);
	while (index > 0)
	{
		index--;
		if (s[index] == (char)c)
			return ((char *)s + index);
	}
	return (NULL);
}
