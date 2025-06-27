/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:47:42 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:47:44 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int open_infile(t_cmd *cmd)
{
    int infile_fd;
    if (cmd->infile)
    {
        infile_fd = open(cmd->infile, O_RDONLY);
        if (infile_fd < 0)
        {
            perror("Error opening input file");
            return -1;
        }
        return (infile_fd);
    }
    return (-1);
}
int open_outfile(t_cmd *cmd)
{
    int outfile_fd;

    if (cmd->outfile)
    {
        if (cmd->append == 0)
            outfile_fd = open(cmd->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
        else
            outfile_fd = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
        
        if (outfile_fd < 0)
        {
            perror("Error opening output file");
            return -1;
        }
        return (outfile_fd);
    }
    return (-1);
}

void redirection(t_cmd *cmd)
{
    int fd;
    if (cmd->infile)
    {
        fd = open_infile(cmd);
        if (fd >= 0)
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
    if (cmd->outfile)
    {
        fd = open_outfile(cmd);
        if (fd >= 0)
        {
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }
}