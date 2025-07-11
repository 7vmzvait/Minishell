/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:34:44 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:34:49 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin_command(char *command)
{
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset"))
	{
		return (1);
	}
	return (0);
}

int	execute_builtins(t_cmd *cmd, t_shell *shell, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(env, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(&cmd->args[0]));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(&cmd->args[0]));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(env, shell, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export1(&shell, &cmd->args[0], env));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(&shell, env, cmd->args));
	return (0);
}

int	run_builtins(t_cmd *cmd, t_shell *shell, t_env *env, t_context *ctx)
{
	int	save_stdin;
	int	save_stdout;

	(void)ctx;
	save_stdin = -1;
	save_stdout = -1;
	if (is_builtin_command(cmd->args[0]))
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		execute_builtins(cmd, shell, env);
		if (save_stdin != -1)
		{
			dup2(save_stdin, STDIN_FILENO);
			close(save_stdin);
		}
		if (save_stdout != -1)
		{
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
		}
	}
	return (g_exit_status);
}
