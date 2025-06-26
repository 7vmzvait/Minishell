/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:23:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:23:18 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *parse_tokens(char **tokens)
{
    t_cmd *cmd_list;
    t_cmd *cmd;
    int i;

    cmd_list = NULL;
    i = 0;
    while (tokens[i])
    {
        if (!cmd_list)
        {
            cmd = new_cmd_node();
            if (!cmd)
                return (NULL);
            cmd_list = cmd;
        }
        else if (ft_strcmp(tokens[i], "|") == 0)
        {
            cmd->pipe_to_next = 1;
            cmd = new_cmd_node();
            if (!cmd)
            {
                free_cmds(cmd_list);
                return (NULL);
            }
            add_cmd_to_list(&cmd_list, cmd);
            i++;
            continue ;
        }
        else if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0)
        {
            set_infile(cmd, tokens[i], tokens[i + 1]);
            i += 2;
            continue ;
        }
        else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
            set_outfile(cmd, tokens[i], tokens[i + 1]);
            i += 2;
            continue ;
        }
        else
        {
            add_arg_to_cmd(cmd, ft_strdup(tokens[i]));
        }
        i++;
    }
    return (cmd_list);
}

t_cmd *parse_input(char *input)
{
    char **tokens;
    t_cmd *cmd_list;

    tokens = tokenize(input);
    if (!tokens)
        return (NULL);
    cmd_list = parse_tokens(tokens);
    free_tokens(tokens);
    return (cmd_list);
}