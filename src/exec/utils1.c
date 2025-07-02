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

char *getenv_path(t_env *env)
{
	t_shell *current;

	current = env->env_list;
	while (current)
	{
		if (ft_strncmp(current->key,"PATH",5) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char **list_to_array(t_env *env,t_shell *shell)
{
        (void)shell;
        t_shell *current;
        int counter;
        char **env_var;

        counter = 0;
        current = env->env_list;
        while (current)
        {
                counter++;
                current = current->next; 
        }
        env_var = malloc((counter + 1) * sizeof(char *));
        current = env->env_list;
        counter = 0;
        while (current)
        {
                env_var[counter++] = ft_create_env_line(current);
                current = current->next;
        }
        env_var[counter] = NULL;
        return (env_var);
}

char	*ft_strjoin_command_with_path(char *cmd,t_shell *shell,t_env *env)
{
	char	**split_path;
	char	*join_slash;
	char	*join_cmd;
	char	*path;
	int		i;

	i = -1;
	
	(void)shell;
	path = getenv_path(env);
	
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

char	*check_command(char *cmd,t_shell *shell,t_env *env)
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
		res = ft_strjoin_command_with_path(cmd,shell,env);
		if (!res)
			return (NULL);
	}
	return (res);
}


void	exec(char **cmd, t_shell *shell,t_env *env)
{
	char	*path;
	char     **env_list;

	env_list = list_to_array(env,shell); // leaks;
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free_split(cmd);
		write(2, "minshell: command not found: \n", 30);
		exit(127);
	}
	path = check_command(cmd[0],shell,env);
	if (!path)
	{
		write(2, "minishell: command not found: ", 29);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		free_split(cmd);
		exit(127);
	}
	if (execve(path, cmd, env_list) == -1)
	{
		free(path);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
}


