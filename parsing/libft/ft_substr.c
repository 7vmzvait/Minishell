/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:00:59 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/19 23:25:13 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*ptr;
	size_t	len_s;
	size_t	sub_size;

	index = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	sub_size = len_s - start;
	if (sub_size > len)
		sub_size = len;
	ptr = (char *)malloc((sub_size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (index < sub_size && s[index + start] != '\0')
	{
		ptr[index] = s[start + index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}
