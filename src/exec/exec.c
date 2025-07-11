/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/07 14:36:44 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parent_process(t_cmd *cmd, t_context *ctx)
{
	if (ctx->prev_pipe != -1)
		close(ctx->prev_pipe);
	if (cmd->next)
		close(ctx->fdpipe[1]);
	ctx->last_pid = ctx->pids;
}

int	execute_commands(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	while (cmd)
	{
		if (cmd->next)
			pipe(ctx->fdpipe);
		ctx->pids = fork();
		if (ctx->pids == 0)
		{
			kill_process();
			child_process(cmd, ctx, shell, env);
		}
		else
			parent_process(cmd, ctx);
		if (cmd->next)
			ctx->prev_pipe = ctx->fdpipe[0];
		else
			ctx->prev_pipe = -1;
		cmd = cmd->next;
	}
	if (ctx->pids != -1)
		waitpid(ctx->last_pid, &g_exit_status, 0);
	while (wait(NULL) > 0)
		;
	g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}
