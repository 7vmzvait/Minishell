/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:47:02 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 18:09:17 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = new_cmd_node();
    if (!current_cmd)
        return NULL;

    add_cmd_to_list(&cmd_list, current_cmd);

    while (tokens)
    {
        if (tokens->type == WORD)
        {
            add_arg_to_cmd(current_cmd, tokens->value);
            tokens = tokens->next;
        }
        else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT ||
                 tokens->type == APPEND || tokens->type == HEREDOC)
        {
            tokens = tokens->next;
            if (!tokens || tokens->type != WORD)
            {
                free_command_list(cmd_list);
                return NULL;
            }
            handle_redir(current_cmd, &tokens);
            tokens = tokens->next;
        }
        else if (tokens->type == PIPE)
        {
            current_cmd->pipe_to_next = 1;
            current_cmd = new_cmd_node();
            if (!current_cmd)
            {
                free_command_list(cmd_list);
                return NULL;
            }
            add_cmd_to_list(&cmd_list, current_cmd);
            tokens = tokens->next;
        }
        else
        {
            // unknown token type, free and exit
            free_command_list(cmd_list);
            return NULL;
        }
    }

    return cmd_list;
}
