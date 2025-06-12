/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:53:08 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/11 10:58:18 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *create_token(char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = value;
    token->type = get_token_type(value);
    token->next = NULL;
    return token;
}

void add_token(t_token **head, t_token *new_token)
{
    t_token *tmp;

    if (!*head)
        *head = new_token;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
}

t_token *tokenize_line(char *line)
{
    t_token *tokens = NULL;
    int i = 0;

    while (line[i])
    {
        while (line[i] == ' ' || line[i] == '\t')
            i++;

        if (!line[i])
            break;

        if (line[i] == '\'' || line[i] == '"')
        {
            char *word = get_quoted_word(line, &i);
            add_token(&tokens, create_token(word));
        }
        else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            int start = i;
            i++;
            // Handle >> or <<
            if ((line[start] == '>' && line[i] == '>') || (line[start] == '<' && line[i] == '<'))
                i++;

            char *sym = ft_strdup_range(line, start, i - start);
            add_token(&tokens, create_token(sym));
        }
        else
        {
            char *word = get_word(line, &i);
            add_token(&tokens, create_token(word));
        }
    }
    return tokens;
}
