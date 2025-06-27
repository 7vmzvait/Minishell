/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:07:10 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void child_process(t_cmd *tmp,t_context *ctx)
{
    
        if (ctx->prev_pipe != -1)
        {
                dup2(ctx->prev_pipe,STDIN_FILENO);
                close(ctx->prev_pipe);
    	}
        if (tmp->next)
        {
                dup2(ctx->fdpipe[1],STDOUT_FILENO);
                close(ctx->fdpipe[0]);
        	    close(ctx->fdpipe[1]);
        }
        // if (tmp->outfile || tmp->infile)
        //     redirection(tmp);
        exec(tmp->args[0],ctx->env);
}

void parent_process(t_cmd *tmp , t_context *ctx)
{
    ctx->last_pid = ctx->pids;
    if (ctx->prev_pipe != -1)
        close(ctx->prev_pipe);
    if (tmp->next)
         close(ctx->fdpipe[1]);
}

int execute_commands(t_cmd *cmd,t_context *ctx)
{
    t_cmd *tmp;
    int status;

    ctx->prev_pipe = -1;
    tmp = cmd;

    while (tmp)
    {
        if (tmp->next)
            pipe(ctx->fdpipe);
        ctx->pids = fork();
        if (ctx->pids == 0)
            child_process(tmp,ctx);
        else
            parent_process(tmp,ctx);
        ctx->prev_pipe = ctx->fdpipe[0];
        tmp = tmp->next;
    }
    waitpid(ctx->last_pid,&status,0);
    while (wait(NULL) > 0);
    return (status);
}
