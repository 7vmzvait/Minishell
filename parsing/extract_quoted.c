/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:02:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:19 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *extract_quoted(const char *input, int *i, int *is_single)
{
    char quote;
    int start, len = 0;

    quote = input[*i];
    *is_single = (quote == '\'');
    if (quote != '\'' && quote != '"')
        return NULL;

    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != quote) {
        (*i)++;
        len++;
    }
    if (input[*i] != quote)
        return NULL;
    (*i)++;
    char *str = malloc(len + 1);
    if (!str) return NULL;
    ft_strncpy(str, &input[start], len);
    str[len] = 0;
    return str;
}