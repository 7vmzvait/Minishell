/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:18:06 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 01:42:01 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;
	size_t			index;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	index = 0;
	if (!dest && !src)
		return (NULL);
	while (index < n)
	{
		cdest[index] = csrc[index];
		index++;
	}
	return (cdest);
}
