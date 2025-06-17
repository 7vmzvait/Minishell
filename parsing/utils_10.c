/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:59:13 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 13:00:25 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
    int len = 0;
    while (cmd->args && cmd->args[len])
        len++;

    char **new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return;

    int i = 0;
    while (i < len)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i++] = ft_strdup(arg);
    new_args[i] = NULL;

    free(cmd->args);
    cmd->args = new_args;
}

void set_infile(t_cmd *cmd, char *redir, char *file)
{
    cmd->infile = ft_strdup(file);
    cmd->heredoc = (redir[0] == '<' && redir[1] == '<');
}

void set_outfile(t_cmd *cmd, char *redir, char *file)
{
    cmd->outfile = ft_strdup(file);
    cmd->append = (redir[0] == '>' && redir[1] == '>');
}
