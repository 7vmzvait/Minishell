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

<<<<<<< HEAD
// void set_infile(t_cmd *cmd, char *redir, char *file)
// {
//     if (cmd->infile)
//         free(cmd->infile);
//     cmd->infile = ft_strdup(file);
//     if (!cmd->infile)
//         return ;
//     if (ft_strcmp(redir, "<") == 0)
//         cmd->heredoc = 0;
//     else if (ft_strcmp(redir, "<<") == 0)
//         cmd->heredoc = 1;
// }

void	set_outfile(t_cmd *cmd, char *redir, char *file)
=======
void set_outfile(t_cmd *cmd, char *redir, char *file)
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(file);
	if (!cmd->outfile)
		return ;
	if (ft_strcmp(redir, ">") == 0)
		cmd->append = 0;
	else if (ft_strcmp(redir, ">>") == 0)
		cmd->append = 1;
}