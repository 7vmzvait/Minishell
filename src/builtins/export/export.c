/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:08:16 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 18:08:46 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	helper_fuc_may(t_shell **shell, t_env *env, char **args)
{
	int		i;
	char	*plus;
	char	*equal;

	i = 1;
	while (args[i])
	{
		plus = ft_strchr(args[i], '+');
		equal = ft_strchr(args[i], '=');
		if (plus && equal)
		{
			if (plus + 1 == equal)
				join_key(shell, args[i], env);
			else
				add_node(shell, args[i], env);
		}
		else
			add_node(shell, args[i], env);
		i++;
	}
}

int	ft_export1(t_shell **shell, char **args, t_env *env)
{
	if (!args[0])
		return (0);
	if (!args[1])
	{
		print_export(env);
		return (g_exit_status);
	}
	if (is_valid_export_syntax(args[1]) != 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	helper_fuc_may(shell, env, args);
	return (g_exit_status);
}
