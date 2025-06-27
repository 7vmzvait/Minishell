/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:37 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/27 13:31:12 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_found(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(const char *s, const char *set)
{
	int		start;
	int		end;
	int		len;
	char	*ptr;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && !is_found(set, s[start]))
		start++;
	end = ft_strlen(s) - 1;
	while (end >= start && !is_found(set, s[end]))
		end--;
	len = end - start + 1;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}
