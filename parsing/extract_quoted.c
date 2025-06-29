/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:02:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/29 19:09:41 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
char *extract_quoted(const char *input, int *i, int *is_single_quote)
{
    char quote = input[*i];  // ' or "
    *is_single_quote = (quote == '\''); // <-- use the parameter ✅
    (*i)++;
    int start = *i;

    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (input[*i] != quote)
        return NULL; // unclosed quote

    int len = *i - start;
    char *quoted = ft_substr(input, start, len);
    (*i)++; // skip closing quote
    return quoted;
}
