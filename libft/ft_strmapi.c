/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:17:15 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/14 19:54:35 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*ptr;
	int		index;

	len = 0;
	index = 0;
	while (s[len])
		len++;
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[index])
	{
		ptr[index] = f(index, s[index]);
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}
