/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:46:06 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:32:40 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *new_cmd_node(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->heredoc = 0;
    cmd->pipe_to_next = 0;
    cmd->next = NULL;
    return cmd;
}

void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
    t_cmd *tmp;

    if (!list || !new_cmd)
        return;
    if (!*list)
        *list = new_cmd;
    else
    {
        tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

void add_arg(char ***args, char *new_arg)
{
    int count = 0;
    char **new_args;

    if (!args)
        return;
    while (*args && (*args)[count])
        count++;
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return;
    for (int i = 0; i < count; i++)
        new_args[i] = (*args)[i];
    new_args[count] = new_arg;
    new_args[count + 1] = NULL;
    free(*args);
    *args = new_args;
}

void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
    if (!cmd || !arg)
        return;
    add_arg(&(cmd->args), arg);
}