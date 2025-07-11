/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:33:03 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 16:34:12 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **split_path)
{
	int	i;

	i = 0;
	if (!split_path)
		return ;
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd->args || !cmd)
		return ;
	tmp = cmd;
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

void	free_env(char **env)
{
	int	i;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
