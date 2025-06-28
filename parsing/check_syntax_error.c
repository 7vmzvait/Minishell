/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:44 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 17:12:09 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_syntax_error(char **tokens)
{
    int i = 0;

    if (!tokens || !tokens[0])
        return 1;

    if (ft_strcmp(tokens[0], "|") == 0)
    {
        printf("syntax error near unexpected token `|'\n");
        return 1;
    }

    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0 &&
            (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0))
        {
            printf("syntax error near unexpected token `|'\n");
            return 1;
        }
        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 ||
             ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0))
        {
            if (!tokens[i + 1])
            {
                printf("syntax error near unexpected token `newline'\n");
                return 1;
            }
            if (is_special(tokens[i + 1][0]))
            {
                printf("syntax error near unexpected token `%s'\n", tokens[i + 1]);
                return 1;
            }
        }
        i++;
    }

    return 0;
}
