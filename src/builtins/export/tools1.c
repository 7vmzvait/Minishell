/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:17:19 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 12:17:28 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_shell	*create_node(char *args)
{
	t_shell	*node;

	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->key = extract_args(args, 'K');
	node->value = extract_args(args, 'V');
	node->next = NULL;
	return (node);
}

void	add_back(t_shell **head, t_shell *last)
{
	t_shell	*tmp;

	if (*head == NULL)
		*head = last;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = last;
	}
}

void	update_env(t_shell **shell, char *args, t_env *env)
{
	t_shell	*tmp;
	char	*key;
	char	*value;

	(void)shell;
	key = extract_args(args, 'K');
	value = extract_args(args, 'V');
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->key);
			free(tmp->value);
			tmp->key = key;
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	free(key);
	free(value);
	add_back(&env->env_list, create_node(args));
}

void	join_key(t_shell **shell, char *args, t_env *env)
{
	t_shell	*tmp;
	char	*join;
	char	*key;
	char	*value;

	(void)shell;
	key = extract_keys(args, 'K');
	value = extract_keys(args, 'V');
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			join = ft_strjoin(tmp->value, value);
			tmp->value = join;
			return ;
		}
		tmp = tmp->next;
	}
	free(key);
	free(value);
}

void	add_node(t_shell **shell, char *last, t_env *env)
{
	if (!last)
		return ;
	else
		update_env(shell, last, env);
}
