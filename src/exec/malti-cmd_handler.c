/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malti-cmd_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:15:38 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 16:15:52 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../parsing/parsing.h"
bool is_parent_only_builtin(char *cmd)
{
    // These must run in parent to be effective
    return (strcmp(cmd, "cd") == 0 || 
            strcmp(cmd, "exit") == 0 || 
            strcmp(cmd, "unset") == 0 ||
            strcmp(cmd, "export") == 0);
}


void	handle_empty_command(t_cmd *cmd)
{
	if (cmd->infile)
		redir_infile(cmd);
	else if (cmd->outfile)
		redir_outfile(cmd);
	exit(g_exit_status);
}

void	setup_input_redirection(t_cmd *cmd, t_context *ctx)
{
	if (cmd->heredoc == 1)
	{
		here_doc(cmd->save_del,cmd);
		if (cmd->save_del)
				free(cmd->save_del);
	}
	else if (cmd->infile)
	{
		if (redir_infile(cmd) < 0)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
	}
	else if (ctx->prev_pipe != -1)
	{
		dup2(ctx->prev_pipe, STDIN_FILENO);
		close(ctx->prev_pipe);
	}
}

void	setup_output_redirection(t_cmd *cmd, t_context *ctx)
{
	if (cmd->outfile)
	{
		if (redir_outfile(cmd) < 0)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
	}
	else if (cmd->next)
	{
		close(ctx->fdpipe[0]);
		dup2(ctx->fdpipe[1], STDOUT_FILENO);
		close(ctx->fdpipe[1]);
	}
}

void	execute_command(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	if (is_builtin_command(cmd->args[0]))
	{
		// if (is_parent_only_builtin(cmd->args[0]) && cmd->pipe_to_next != 1)
		// {
		// 	run_builtins(cmd,shell,env,ctx);
		// 	return;
		// }
		// else
		// {
			run_builtins(cmd,shell,env,ctx);
			exit(0);
		// }

	}
	else
		exec(cmd->args, shell, env, cmd);
}

void	child_process(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	if (!cmd->args)
		handle_empty_command(cmd);
	setup_input_redirection(cmd, ctx);
	setup_output_redirection(cmd, ctx);
	execute_command(cmd, ctx, shell, env);
}
