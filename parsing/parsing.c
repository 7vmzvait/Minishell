/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:31:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:24:34 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../include/minishell.h"

t_cmd *parse_input(char *input,t_env *env)
{
    char **tokens;
    t_cmd *cmds;

    tokens = tokenize(input,env);

    if (!tokens)
        return (NULL);
    if (check_syntax_error(tokens))
    {
        free_tokens(tokens);
        return (NULL);
    }
    cmds = parse_tokens1(tokens);
    return (cmds);
}
