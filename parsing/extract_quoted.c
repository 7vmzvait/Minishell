/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:02:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/29 11:59:10 by haitaabe         ###   ########.fr       */
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
    char quote = input[*i]; // ' or "
    *is_single_quote = (quote == '\''); // set flag
    (*i)++; // move past opening quote

    int start = *i;

    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (input[*i] != quote)
    {
        // 🚨 Unclosed quote found!
        ft_putstr_fd("syntax error: unclosed quote\n", 2);
        return NULL;
    }

    int len = *i - start;
    char *quoted = ft_substr(input, start, len);

    (*i)++;

    return quoted;
}
