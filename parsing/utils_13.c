/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:24:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 20:18:55 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
char *ft_strndup(const char *s, int n)
{
    char *res = malloc(n + 1);
    int j = 0;
    if (!res)
        return NULL;
    while (j < n)
    {
        res[j] = s[j];
        j++;
    }
    res[j] = '\0';
    return res;
}

char *get_special_token(const char *input, int *i)
{
    int start = *i;
    (*i)++;
    if ((input[start] == '<' && input[*i] == '<') ||
        (input[start] == '>' && input[*i] == '>'))
        (*i)++;
    return ft_strndup(input + start, *i - start);
}

char *get_quoted_token(const char *input, int *i)
{
    char quote = input[*i];
    int start = ++(*i); // skip opening quote
    while (input[*i] != '\0' && input[*i] != quote)
        (*i)++;
    char *token = ft_strndup(input + start, *i - start);
    if (input[*i] == quote)
        (*i)++; // skip closing quote
    return token;
}

char *get_word_token(const char *input, int *i)
{
    int start = *i;
    while (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '\t' && !is_special_char(input[*i]) && input[*i] != '\'' && input[*i] != '"')
        (*i)++;
    return ft_strndup(input + start, *i - start);
}

int tokenizer(const char *input, char *tokens[MAX_TOKENS])
{
    int i = 0;
    int t = 0;

    while (input[i] != '\0' && t < MAX_TOKENS - 1)
    {
        skip_spaces(input, &i);
        if (input[i] == '\0')
            break;

        if (is_special_char(input[i]))
            tokens[t++] = get_special_token(input, &i);
        else if (input[i] == '\'' || input[i] == '"')
            tokens[t++] = get_quoted_token(input, &i);
        else
            tokens[t++] = get_word_token(input, &i);
    }
    tokens[t] = NULL;
    return t;
}