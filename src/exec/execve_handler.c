/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:30:45 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 16:31:46 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	validate_command(char **cmd, char **env_list)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free_env(env_list);
		write(2, "minshell: command not found: \n", 30);
		exit(127);
	}
}

void	print_command_not_found(char **cmd)
{
	write(2, "minishell: command not found: ", 31);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n", 1);
}

void	cleanup_not_found(char *path, char **env_list, t_cmd *cmd2, t_env *env)
{
	free(path);
	free_env(env_list);
	free_cmds(cmd2);
	free_env_var_list(env);
	exit(127);
}

void	cleanup_and_exit_failure(char *path, char **env_list, t_cmd *cmd2,
		t_env *env)
{
	(void)path;
	// free(path);
	free_env(env_list);
	free_cmds(cmd2);
	free_env_var_list(env);
	// free(env);
	exit(EXIT_FAILURE);
}

void	exec(char **cmd, t_shell *shell, t_env *env, t_cmd *cmd2)
{
	char	*path;
	char	**env_list;

	env_list = list_to_array(env, shell);
	validate_command(cmd, env_list);
	path = check_command(cmd[0], env);
	if (!path)
	{
		print_command_not_found(cmd);
		cleanup_not_found(path, env_list, cmd2, env);
	}
	if (execve(path, cmd, env_list) == -1)
	{
		free(shell);
		cleanup_and_exit_failure(path, env_list, cmd2, env);
	}
}
