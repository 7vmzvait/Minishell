/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:02:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/30 09:31:04 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "parsing.h"

char *extract_quoted(const char *input, int *i, int *is_single_quote)
{
    char quote = input[*i];
    (*i)++;

    int start = *i;
    int len = 0;

    while (input[*i] && input[*i] != quote)
    {
        (*i)++;
        len++;
    }
    if (input[*i] != quote)
        return NULL;

    char *quoted = ft_substr(input, start, len);

    (*i)++;
    *is_single_quote = (quote == '\'');

    return quoted;
}
