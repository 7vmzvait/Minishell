/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:55:09 by haitaabe          #+#    #+#             */
/*   Updated: 2025/04/30 17:04:19 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_is_space(int check_s)
{
    return (check_s == 32 || (check_s >= 9 && check_s <= 13));
}


int skip_spaces(char *str, int i)
{
    while (str[i] && check_is_space(str[i]))
        i++;
    return i;
}
int skip_quotes(char *str, int i)
{
    char quote;
    if (str[i] == '\'' || str[i] == '"')
    {
        quote = str[i];
        i++;
        while (str[i] && str[i] != quote)
            i++;
        if (str[i] == quote)
            i++;
    }

    return i;
}
