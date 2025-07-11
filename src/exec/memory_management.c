/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:35:36 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:35:41 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_kv(t_shell *shell)
{
	if (shell->key)
	{
		free(shell->key);
		shell->key = NULL;
	}
	if (shell->value)
	{
		free(shell->value);
		shell->value = NULL;
	}
	free(shell);
}

void	cleanup_memory(t_cmd *cmd, t_context *ctx, t_env *env, t_shell *shell)
{
	(void)cmd;
	if (env)
	{
		free_env_var_list(env);
		free(env);
	}
	if (ctx)
		free(ctx);
	if (shell)
		free(shell);
}

void	free_env_var_list(t_env *head)
{
	t_shell	*current;
	t_shell	*next;

	current = head->env_list;
	while (current)
	{
		next = current->next;
		free_env_kv(current);
		current = next;
	}
	free(head);
}
