/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:22 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 21:21:35 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char *extract_word(const char *input, int *i)
// {
//     int start = *i;
//     int len = 0;

//     while (input[*i] && !is_space(input[*i]) && !is_special(input[*i]))
//     {
//         (*i)++;
//         len++;
//     }
//     return ft_substr(input, start, len);
// }
char *extract_word(const char *input, int *i)
{
    char *result = ft_strdup("");
    char *fragment;

    while (input[*i] && !is_space(input[*i]) && !is_special(input[*i]))
    {
        if (input[*i] == '\'' || input[*i] == '"')
        {
            int is_single_quote = 0;
            fragment = extract_quoted(input, i, &is_single_quote);
        }
        else
        {
            fragment = extract_unquoted(input, i);
        }

        if (!fragment)
            return NULL;

        char *tmp = result;
        result = ft_strjoin(result, fragment);
        free(tmp);
        free(fragment);
    }
    return result;
}

char *extract_unquoted(const char *input, int *i)
{
    int start = *i;

    while (input[*i] && !is_space(input[*i]) &&
           !is_special(input[*i]) &&
           input[*i] != '\'' && input[*i] != '"')
    {
        (*i)++;
    }

    return ft_substr(input, start, *i - start);
}
