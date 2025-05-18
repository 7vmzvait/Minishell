/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:48:24 by eazmir            #+#    #+#             */
/*   Updated: 2025/02/08 15:34:38 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	i = 0;
	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	while (cs1[i] && cs2[i] && cs1[i] == cs2[i] && i < n -1)
	{
		i++;
	}
	return (cs1[i] - cs2[i]);
}
