/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:17:18 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 18:17:34 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
void handle_redir(t_cmd *cmd, char **tokens, int *i)
{
    if (!ft_strcmp(tokens[*i], "<"))
        cmd->infile = ft_strdup(tokens[++(*i)]);
    else if (!ft_strcmp(tokens[*i], ">"))
        cmd->outfile = ft_strdup(tokens[++(*i)]);
    else if (!ft_strcmp(tokens[*i], ">>"))
    {
        cmd->outfile = ft_strdup(tokens[++(*i)]);
        cmd->append = 1;
    }
    else if (!ft_strcmp(tokens[*i], "<<"))
    {
        cmd->infile = ft_strdup(tokens[++(*i)]);
        cmd->heredoc = 1;
    }
}
