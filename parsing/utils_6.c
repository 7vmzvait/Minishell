/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:11:57 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/13 17:28:00 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void skip_spaces(char *line, int *i)
{
    while (line[*i] == ' ')
        (*i)++;
}
int count_tokens(char *line)
{
    int i = 0;
    int count = 0;

    while (line[i])
    {
        skip_spaces(line, &i);
        if (!line[i])
            break;

        int len = get_token_len(line, i);
        if (len > 0)
        {
            count++;
            i += len;
        }
    }
    return count;
}
char **tokenize(char *line)
{
    int i = 0;
    int token_idx = 0;
    int count = count_tokens(line);

    char **tokens = malloc(sizeof(char *) * (count + 1));
    if (!tokens)
        return NULL;

    while (line[i])
    {
        skip_spaces(line, &i);
        if (!line[i])
            break;

        int len = get_token_len(line, i);
        if (len > 0)
        {
            tokens[token_idx] = ft_substr(line, i, len); // assumes ft_substr works like strndup
            token_idx++;
            i += len;
        }
    }
    tokens[token_idx] = NULL;
    return tokens;
}
