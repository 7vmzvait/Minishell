/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:21:18 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

char **tokenize(char *line)
{
    char **tokens;
    int i;
    int j;
    int count;
    int len;

    i = 0;
    count = 0;
    // Count tokens roughly (to allocate)
    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;
        len = 0;
        if (is_special_char(line[i]))
        {
            len++;
            if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
                len++;
        }
        else
        {
            while (line[i + len] && !is_space(line[i + len]) && !is_special_char(line[i + len]))
                len++;
        }
        count++;
        i += len;
    }
    tokens = malloc(sizeof(char *) * (count + 1));
    if (!tokens)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;
        len = get_token_len(line, i);
        tokens[j] = ft_substr(line, i, len);
        if (!tokens[j])
        {
            while (j > 0)
            {
                free(tokens[j - 1]);
                j--;
            }
            free(tokens);
            return (NULL);
        }
        j++;
        i += len;
    }
    tokens[j] = NULL;
    return (tokens);
}