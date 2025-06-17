/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:54:25 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 12:55:22 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *extract_word(const char *input, int *i)
{
    int start = *i;
    int len = 0;

    while (input[*i] && !is_space(input[*i]) && !is_special(input[*i]))
    {
        (*i)++;
        len++;
    }

    char *word = malloc(len + 1);
    if (!word)
        return NULL;

    int j = 0;
    while (j < len)
    {
        word[j] = input[start + j];
        j++;
    }
    word[len] = '\0';
    return word;
}

char *extract_special(const char *input, int *i)
{
    int start = *i;
    int len = 1;

    if ((input[*i] == '<' && input[*i + 1] == '<') ||
        (input[*i] == '>' && input[*i + 1] == '>'))
    {
        (*i) += 2;
        len = 2;
    }
    else
        (*i)++;

    char *symbol = malloc(len + 1);
    if (!symbol)
        return NULL;

    int j = 0;
    while (j < len)
    {
        symbol[j] = input[start + j];
        j++;
    }
    symbol[len] = '\0';
    return symbol;
}

char *extract_quoted(const char *input, int *i)
{
    char quote = input[*i];
    int start;

    (*i)++; // skip the opening quote
    start = *i;

    int len = 0;
    while (input[*i] && input[*i] != quote)
    {
        (*i)++;
        len++;
    }

    char *quoted = malloc(len + 1);
    if (!quoted)
        return NULL;

    int j = 0;
    while (j < len)
    {
        quoted[j] = input[start + j];
        j++;
    }
    quoted[len] = '\0';

    if (input[*i] == quote)
        (*i)++; // skip closing quote

    return quoted;
}
