/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:31:22 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 01:16:16 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*cs;
	unsigned char	cc;

	cc = (unsigned char)c;
	cs = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (cs[index] == cc)
			return (cs + index);
		index++;
	}
	return (NULL);
}
