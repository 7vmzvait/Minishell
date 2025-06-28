/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:29:50 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:06:08 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	return (env[i]);
}

char	*join_command_with_path(char *cmd, char **env)
{
	char	**split_path;
	char	*join_slash;
	char	*join_cmd;
	char	*path;
	int		i;

	i = -1;
	path = get_path(env);
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	while (split_path[++i])
	{
		join_slash = ft_strjoin(split_path[i], "/");
		join_cmd = ft_strjoin(join_slash, cmd);
		free(join_slash);
		if (access(join_cmd, F_OK | X_OK) == 0)
		{
			free_split(split_path);
			return (join_cmd);
		}
		free(join_cmd);
	}
	free_split(split_path);
	return (NULL);
}

char	*check_command(char *cmd, char **env)
{
	char	*res;

	res = NULL;
	if (cmd == NULL || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	else
	{
		res = join_command_with_path(cmd, env);
		if (!res)
			return (NULL);
	}
	return (res);
}

void	exec(char **cmd, char **env)
{
	// char	**cmd;
	char	*path;

	// cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free_split(cmd);
		write(2, "minshell: command not found: \n", 30);
		exit(127);
	}
	path = check_command(cmd[0], env);
	if (!path)
	{
		write(2, "minishell: command not found: ", 29);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		free_split(cmd);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
}


