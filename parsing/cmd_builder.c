/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:20:56 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:47 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// t_cmd *new_cmd_node(void)
// {
//     t_cmd *cmd;

//     cmd = malloc(sizeof(t_cmd));
//     if (!cmd)
//         return (NULL);
//     cmd->args = NULL;
//     cmd->infile = NULL;
//     cmd->outfile = NULL;
//     cmd->append = 0;
//     cmd->heredoc = 0;
//     cmd->pipe_to_next = 0;
//     cmd->next = NULL;
//     return (cmd);
// }

//void add_arg_to_cmd(t_cmd *cmd, char *arg)
//{
   //  add_arg(&(cmd->args), arg);
//}

/*
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
    t_cmd *tmp;

    if (!*list)
    {
        *list = new_cmd;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_cmd;
}
*/
