/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:52:23 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 17:31:14 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type get_token_type(char *str)
{

    if (!str || !str[0])
        return WORD;

    if (ft_strcmp(str, "|") == 0)
        return PIPE;
    else if (ft_strcmp(str, "<") == 0)
        return REDIR_IN;
    else if (ft_strcmp(str, ">") == 0)
        return REDIR_OUT;
    else if (ft_strcmp(str, ">>") == 0)
        return APPEND;
    else if (ft_strcmp(str, "<<") == 0)
        return HEREDOC;
    else
        return WORD;
}

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
    cmd->next = NULL;
    return cmd;
}

void add_arg(char ***args, char *new_arg)
{
    int count = 0;
    char **new_args;

    if (*args)
    {
        while ((*args)[count])
            count++;
    }
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return;

    int i = 0;
    while (i < count)
    {
        new_args[i] = (*args)[i];
        i++;
    }

    new_args[count] = ft_strdup(new_arg);
    new_args[count + 1] = NULL;
    if (*args)
        free(*args);
    *args = new_args;
}

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