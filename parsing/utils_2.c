/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:52:23 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/16 16:38:10 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int simplify_tokens(char *line)
{
    if (ft_strncmp(line, "|", 1) == 0)
        return PIPE;
    else if (ft_strncmp(line, "<", 1) == 0)
        return REDIR_IN;
    else if (ft_strncmp(line, ">", 1) == 0)
        return REDIR_IN;
    else if (ft_strncmp(line, ">>", 2) == 0)
        return APPEND;
    else if (ft_strncmp(line, "<<", 2) == 0)
        return HEREDOC;
    else
        WORD;
}

// we used it to store command info like we got from the user
t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL; // handle malloc error
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->pipe_to_next = 0;
    cmd->next = NULL;
    return cmd;
}
// this function how you build the list like: ["ls", "-l", NULL]
void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
    int count = 0;

    if (cmd->args)
    {
        while (cmd->args[count])
            count++;
    }

    char **new_args = malloc(sizeof(char *) * (count + 2));
    int i = 0;
    while (i < count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[count] = ft_strdup(arg);
    new_args[count + 1] = NULL;

    free(cmd->args);
    cmd->args = new_args;
}

// To link commands together (
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
    if (!*list)
        *list = new_cmd;
    else
    {
        t_cmd *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}
