/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:42 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/28 18:39:27 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int  update_env_path(t_shell **shell,char *key, char *new_value)
{
	t_shell *tmp;
	
	tmp = *shell;
	while (tmp)
	{
		if (ft_strncmp(tmp->key,key,ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	cd(t_shell **shell, char **args)
{
	char	new_path[1024];
	char	old_path[1024];
	char	*path;

	getcwd(old_path,sizeof(new_path));
	if (!args[1])
		path = getenv("HOME");
	else if (ft_strncmp(args[1], "-", 1) == 0)
		path = getenv("OLDPWD");
	else
		path = args[1];
	chdir(path);
	getcwd(new_path,sizeof(new_path));
	update_env_path(shell,"PWD",new_path);
}
