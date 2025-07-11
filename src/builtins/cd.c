/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:42 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 18:01:29 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_env_path(t_env *env, char *key, char *new_value)
{
	t_shell	*tmp;

	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_cd(t_env *env, char **args)
{
	char	new_path[1024];
	char	old_path[1024];
	char	*path;

	getcwd(old_path, sizeof(new_path));
	if (!args[1])
		path = getenv("HOME");
	else if (ft_strncmp(args[1], "-", 1) == 0)
		path = getenv("OLDPWD");
	else
		path = args[1];
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	chdir(path);
	getcwd(new_path, sizeof(new_path));
	update_env_path(env, "PWD", new_path);
	return (g_exit_status);
}
