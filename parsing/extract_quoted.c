/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:02:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 21:19:43 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char *extract_quoted(const char *input, int *i)
// {
//     int start, len = 0;
//     char quote;

//     quote = input[*i];
//     if (quote != '\'' && quote != '\"')
//         return NULL;

//     (*i)++; // Skip opening quote
//     start = *i;

//     while (input[*i] && input[*i] != quote)
//     {
//         (*i)++;
//         len++;
//     }

//     if (input[*i] == quote)
//         (*i)++; // Skip closing quote

//     return ft_substr(input, start, len);
// }
char *extract_quoted(const char *input, int *i, int *is_single_quote)
{
    char quote = input[*i]; // either ' or "
    *is_single_quote = (quote == '\'');  // set flag for later

    (*i)++;  // skip the opening quote

    int start = *i;
    while (input[*i] && input[*i] != quote)
        (*i)++;

    int len = *i - start;
    char *quoted = ft_substr(input, start, len);

    if (input[*i] == quote)
        (*i)++;  // skip the closing quote

    return quoted;
}
