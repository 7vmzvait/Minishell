/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:44 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:50 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_syntax_error(char **tokens)
{
    int i = 0;

    if (!tokens || !tokens[0])
        return 1;

    if (ft_strcmp(tokens[0], "|") == 0)
        return 1;

    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0 && (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0))
            return 1;

        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 ||
             ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0) &&
            (!tokens[i + 1] || is_special(tokens[i + 1][0])))
            return 1;

        i++;
    }

    return 0; // no syntax error
}