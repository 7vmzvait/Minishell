/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:26:59 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:27:21 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_valid_var_char(char c)
{
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            (c == '_'));
}

char *extract_var_name(const char *str, int *index)
{
    int start;
    int len;
    char *var_name;

    start = *index;
    len = 0;
    while (str[*index] && is_valid_var_char(str[*index]))
    {
        (*index)++;
        len++;
    }
    var_name = malloc(len + 1);
    if (!var_name)
        return (NULL);
    len = 0;
    while (str[start] && is_valid_var_char(str[start]))
    {
        var_name[len++] = str[start++];
    }
    var_name[len] = '\0';
    return (var_name);
}