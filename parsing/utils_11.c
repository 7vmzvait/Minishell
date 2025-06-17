/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:05:30 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 18:10:11 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_word(const char *line, int *i)
{
    int start;
    int len = 0;

    start = *i;

    while (line[*i] && line[*i] != ' ' && !is_special(line[*i]) &&
           line[*i] != '"' && line[*i] != '\'')
    {
        (*i)++;
        len++;
    }

    return (ft_substr(line, start, len));
}
char *get_quoted_word(const char *line, int *i)
{
    int start;
    int len = 0;
    char quote;

    quote = line[*i]; // could be ' or "
    (*i)++;           // skip the opening quote
    start = *i;

    while (line[*i] && line[*i] != quote)
    {
        (*i)++;
        len++;
    }
    // move past the closing quote if it exists
    if (line[*i] == quote)
        (*i)++;

    return (ft_substr(line, start, len));
}
char *get_special_token(const char *line, int *i)
{
    char c;
    int start;

    c = line[*i]; // could be < > |
    start = *i;
    (*i)++; // move past first symbol

    // check for double special like << or >>
    if ((c == '<' || c == '>') && line[*i] == c)
        (*i)++;

    return (ft_substr(line, start, *i - start));
}

char **tokenizer(const char *line)
{
    char **tokens;
    int i = 0;
    int j = 0;

    tokens = malloc(sizeof(char *) * (ft_strlen(line) + 1));
    if (!tokens)
        return NULL;

    while (line[i])
    {
        skip_spaces(&i, line);

        if (line[i] == '\0')
            break;

        if (line[i] == '\'' || line[i] == '"')
            tokens[j++] = get_quoted_word(line, &i);
        else if (is_special(line[i]))
            tokens[j++] = get_special_token(line, &i);
        else
            tokens[j++] = get_word(line, &i);
    }
    tokens[j] = NULL;
    return tokens;
}
