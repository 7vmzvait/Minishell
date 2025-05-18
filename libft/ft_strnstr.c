/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:32:30 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 01:31:50 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_(const char *big, const char *little, size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (i < len && big[i] == little[j])
	{
		i++;
		j++;
		if (little[j] == '\0')
			return ((char *)(big + i - j));
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			result = find_(big, little, len, i);
			if (result)
				return (result);
		}
		i++;
	}
	return (NULL);
}
