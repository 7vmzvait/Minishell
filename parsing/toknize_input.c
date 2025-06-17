/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toknize_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:01:07 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 19:01:31 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **tokenize_input(char *str)
{
    char    **tokens;
    int     i = 0;
    int     count = 0;

    tokens = malloc(sizeof(char *) * (MAX_TOKENS)); // define MAX_TOKENS as a safe limit
    if (!tokens)
        return (NULL);

    while (str[i])
    {
        skip_spaces(str, &i);

        if (str[i] == '\0')
            break;

        if (str[i] == '\'' || str[i] == '"')
            add_token(tokens, get_quoted(str, &i), &count);
        else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            add_token(tokens, get_operator(str, &i), &count);
        else
            add_token(tokens, get_word(str, &i), &count);
    }

    tokens[count] = NULL;
    return (tokens);
}
