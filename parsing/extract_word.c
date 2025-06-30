/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:22 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:01:29 by haitaabe         ###   ########.fr       */
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
    return ft_substr(input, start, len);
}