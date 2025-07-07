/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:12 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:59 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	handle_redir(t_cmd *cmd, t_token **token)
// {
// 	if (!cmd || !token || !*token)
// 		return ;
// 	t_token *redir_token = *token;           // The redirection token (e.g., >,
// 			>>)
// 	t_token *file_token = redir_token->next; // The filename token
// 	if (!file_token || file_token->type != WORD)
// 		return ; // handle error or invalid syntax
// 	if (redir_token->type == REDIR_IN)
// 		cmd->infile = ft_strdup(file_token->value);
// 	else if (redir_token->type == REDIR_OUT)
// 	{
// 		cmd->outfile = ft_strdup(file_token->value);
// 		cmd->append = 0;
// 	}
// 	else if (redir_token->type == APPEND)
// 	{
// 		cmd->outfile = ft_strdup(file_token->value);
// 		cmd->append = 1;
// 	}
// 	else if (redir_token->type == HEREDOC)
// 	{
// 		cmd->heredoc = 1;
// 	}
// 	*token = file_token->next;
// }

<<<<<<< HEAD
// void	set_infile(t_cmd *cmd, char *redir, char *file)
// {
// 	(void)redir;
// 	if (cmd->infile)
// 		free(cmd->infile);
// 	cmd->infile = ft_strdup(file);
// }

// void set_outfile(t_cmd *cmd, char *redir, char *file)
// {
//     (void)redir;
//     if (cmd->outfile)
//         free(cmd->outfile);
//     cmd->outfile = ft_strdup(file);
// }
=======
    t_token *redir_token = *token;
    t_token *file_token = redir_token->next;

    if (!file_token || file_token->type != WORD)
        return;

    if (redir_token->type == REDIR_IN)
        cmd->infile = ft_strdup(file_token->value);
    else if (redir_token->type == REDIR_OUT)
    {
        cmd->outfile = ft_strdup(file_token->value);
        cmd->append = 0;
    }
    else if (redir_token->type == APPEND)
    {
        cmd->outfile = ft_strdup(file_token->value);
        cmd->append = 1;
    }
    else if (redir_token->type == HEREDOC)
    {
        cmd->heredoc = 1;
    }
    *token = file_token->next;
}

void set_infile(t_cmd *cmd, char *redir, char *file)
{
    (void)redir;
    if (cmd->infile)
        free(cmd->infile);
    cmd->infile = ft_strdup(file);
}
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
