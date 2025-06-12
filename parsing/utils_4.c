/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:40:37 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/12 12:05:18 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}
char *ft_strdup_range(char *str, int start, int len)
{
    char *new_str; 
    int i;

    new_str = malloc(len + 1);
    if (!new_str)
        return NULL;

    i = 0;
    while (i < len)
    {
        new_str[i] = str[start + i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}

char *get_quoted_word(char *line, int *i)
{
    char quote;
    int start;
    int len;
    char *word;

    quote = line[*i];
    (*i)++;
    start = *i;

    while (line[*i] && line[*i] != quote)
        (*i)++;

    len = *i - start;

    word = ft_strdup_range(line, start, len);

    if (line[*i] == quote)
        (*i)++;

    return word;
}

char *get_word(char *line, int *i)
{
    int start = *i;

    while (line[*i] && !is_space(line[*i]) && !is_quote(line[*i]) && !is_special_char(line[*i]))
        (*i)++;

    return ft_strdup_range(line, start, *i - start);
}