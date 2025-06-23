/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:14:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 14:21:19 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_token(char *line, int *i)
{
    int start = *i;
    int len = 0;
    char *token;
    int j;

    if (is_operator(line[*i]))
    {
        if (line[*i] == '<' && line[*i + 1] == '<')
        {
            *i += 2;
            return ft_strdup("<<");
        }
        else if (line[*i] == '>' && line[*i + 1] == '>')
        {
            *i += 2;
            return ft_strdup(">>");
        }
        else
        {
            token = malloc(2);
            if (!token)
                return NULL;
            token[0] = line[*i];
            token[1] = '\0';
            (*i)++;
            return token;
        }
    }

    while (line[*i] && !is_operator(line[*i]) && line[*i] != ' ')
    {
        (*i)++;
        len++;
    }

    token = malloc(len + 1);
    if (!token)
        return NULL;

    j = 0;
    while (j < len)
    {
        token[j] = line[start + j];
        j++;
    }
    token[j] = '\0';
    return token;
}

char **tokenize_input(char *line)
{
    char **tokens;
    int i;
    int j;

    tokens = malloc(sizeof(char *) * MAX_TOKENS);
    if (!tokens)
        return NULL;

    i = 0;
    j = 0;
    while (line[i])
    {
        skip_spaces(line, &i);
        if (!line[i])
            break;

        tokens[j] = get_token(line, &i);
        if (!tokens[j])
            break;
        j++;
    }
    tokens[j] = NULL;
    return tokens;
}