/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:40:43 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:26:19 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

int	get_token_len(char *line, int i)
{
	int	len;

	len = 0;
	if (is_special(line[i]))
	{
		if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
				+ 1] == '<'))
			return (2);
		return (1);
	}
	while (line[i + len] && !is_space(line[i + len]) && !is_special(line[i
			+ len]))
		len++;
	return (len);
}

char *ft_strncpy(char *dest, const char *src, unsigned int n)
{
    unsigned int i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *ft_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';

    return dest;
}
