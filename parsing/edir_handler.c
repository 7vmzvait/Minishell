/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edir_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:22:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:22:47 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void set_outfile(t_cmd *cmd, char *redir, char *file)
{
    if (cmd->outfile)
        free(cmd->outfile);
    cmd->outfile = ft_strdup(file);
    if (!cmd->outfile)
        return;
    if (ft_strcmp(redir, ">") == 0)
        cmd->append = 0;
    else if (ft_strcmp(redir, ">>") == 0)
        cmd->append = 1;
}