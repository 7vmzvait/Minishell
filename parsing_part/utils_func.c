/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:55:09 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/02 11:35:29 by haitaabe         ###   ########.fr       */
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

char **tokenize(char *line)
{
   int i = 0;
   t_word *save_tokens= (t_word *)malloc(sizeof(t_word));
   while (line[i] != '\0')
   {
        if (check_is_space(line[i]))
            skip_spaces(line, i);
        else if (check_d_q(line[i]) || check_s_q(line[i]))
            skip_quotes(line, i);
        else if (check_types(&line[i]))
            check_types(line);
   }
   line[i] = '\0';
   return (line);
}