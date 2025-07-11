/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:35:21 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:35:25 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*init_env(char **env)
{
	int		i;
	t_env	*env_var;
	t_shell	*new_node;

	env_var = malloc(sizeof(t_env));
	env_var->env_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = create_node(env[i]);
		add_back(&env_var->env_list, new_node);
		i++;
	}
	return (env_var);
}
