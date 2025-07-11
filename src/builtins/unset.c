/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:54 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 18:01:57 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unlink_variable_node(t_shell **shell, t_env *env, char *args)
{
	t_shell	*tmp;
	t_shell	*prev;
	t_shell	*next;

	prev = NULL;
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, args, ft_strlen(args)) == 0)
		{
			next = tmp->next;
			if (prev == NULL)
				*shell = next;
			else
				prev->next = next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_shell **shell, t_env *env, char **args)
{
	int	i;

	if (!args[1] || !args[0])
		return (0);
	i = 1;
	while (args[i])
	{
		if (unlink_variable_node(shell, env, args[i]))
		{
			g_exit_status = 0;
			return (g_exit_status);
		}
		i++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
