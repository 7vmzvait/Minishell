/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:34:19 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/21 16:30:45 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	jndex;
	size_t	index;
	char	*ptr;

	jndex = 0;
	index = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (index < ft_strlen((s1)))
	{
		ptr[index] = s1[index];
		index++;
	}
	while (jndex < ft_strlen(s2))
		ptr[index++] = s2[jndex++];
	ptr[index] = '\0';
	return (ptr);
}
