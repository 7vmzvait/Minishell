/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:26:39 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/13 17:26:49 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
int get_token_len(char *line, int i)
{
    int start = i;

    // Case 1: Quoted token
    if (line[i] == '\'' || line[i] == '\"')
    {
        char quote = line[i++];
        while (line[i] && line[i] != quote)
            i++;
        if (line[i] == quote)
            i++; // skip closing quote
    }
    // Case 2: Special symbols like <, >, >>
    else if (is_special_char(line[i]))
    {
        if (line[i] == '>' && line[i + 1] == '>')
            i += 2;
        else
            i++;
    }
    // Case 3: Normal word
    else
    {
        while (line[i] && !is_special_char(line[i]) && line[i] != ' ' && line[i] != '\t')
            i++;
    }
    return i - start;
}
