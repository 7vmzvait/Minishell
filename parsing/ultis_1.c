/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultis_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:49:56 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/16 16:35:21 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_space(int check_s)
{
    return (check_s == 32 || (check_s >= 9 && check_s <= 13));
}
int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}
// we used it to manage our parsing part like the tokens that we have in it
t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = NULL;
    t_token *token = tokens;
    current_cmd = create_cmd();

    while (token)
    {
        if (token->type == WORD)
        {
            add_arg_to_cmd(current_cmd, token->value);
        }
        else if (token->type == REDIR_IN)
        {
            token = token->next;
            if (!token)
                perror("Missing input file");
            current_cmd->infile = ft_strdup(token->value);
        }
        else if (token->type == REDIR_OUT)
        {
            token = token->next;
            if (!token)
                perror("Missing output file");
            current_cmd->outfile = ft_strdup(token->value);
            current_cmd->append = 0;
        }
        else if (token->type == APPEND)
        {
            token = token->next;
            if (!token)
                perror("Missing output file");
            current_cmd->outfile = ft_strdup(token->value);
            current_cmd->append = 1;
        }
        else if (token->type == PIPE)
        {
            current_cmd->pipe_to_next = 1;
            add_cmd_to_list(&cmd_list, current_cmd); // link the current cmd
            current_cmd = create_cmd();              // start next command
        }
        token = token->next;
    }

    // Add the last command
    if (current_cmd)
        add_cmd_to_list(&cmd_list, current_cmd);

    return cmd_list;
}
