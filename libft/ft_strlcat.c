/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:11:50 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 00:54:11 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	index;
	size_t	jndex;
	size_t	len2;
	size_t	len1;

	if ((!dst || !src) && n == 0)
		return (0);
	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	index = len1;
	jndex = 0;
	if (n == 0 || n <= len1)
		return (len2 + n);
	while (src[jndex] && index < n - 1)
	{
		dst[index] = src[jndex];
		index++;
		jndex++;
	}
	dst[index] = '\0';
	return (len1 + len2);
}
