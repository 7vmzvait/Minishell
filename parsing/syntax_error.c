/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:28:27 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 17:16:09 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_syntax_error(char **tokens)
{
    int i;

    if (!tokens || !tokens[0])
        return (1);

    if (ft_strcmp(tokens[0], "|") == 0)
    {
        printf("syntax error: unexpected token `|'\n");
        return (1);
    }

    i = 0;
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0 &&
            (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0))
        {
            printf("syntax error: unexpected token `|'\n");
            return (1);
        }
        
        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0 ||
             ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0) &&
            !tokens[i + 1])
        {
            printf("syntax error: missing filename after redirection\n");
            return (1);
        }
        i++;
    }
    return (0);
}
