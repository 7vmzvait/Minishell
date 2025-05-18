/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:44:01 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/21 16:16:34 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wc_words(const char *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			flag = 0;
		else if (flag == 0)
		{
			count++;
			flag = 1;
		}
		i++;
	}
	return (count);
}

static char	**free_split(char **ptr, int index)
{
	int	i;

	if (ptr)
	{
		i = 0;
		while (i < index)
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
	return (NULL);
}

static char	**ft_split_v1(char **ptr, const char *s, char c)
{
	int	i;
	int	index;
	int	start;

	i = 0;
	index = 0;
	if (!ptr || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
		{
			ptr[index] = ft_substr(s, start, i - start);
			if (!ptr[index])
				return (free_split(ptr, index));
			index++;
		}
	}
	ptr[index] = NULL;
	return (ptr);
}

char	**ft_split(const char *s, const char c)
{
	char	**ptr;
	int		wc;

	if (!s)
		return (NULL);
	wc = wc_words(s, c);
	ptr = (char **)malloc((wc + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ft_split_v1(ptr, s, c));
}
