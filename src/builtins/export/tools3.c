/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:20:32 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 12:20:36 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	printList(t_shell **shell)
{	
	t_shell *tmp;
	int 	len;
	int	i;
	char 	**env_path;
	char	**_;
	
	tmp = *shell;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	tmp = *shell;
	env_path = malloc((len + 1) * sizeof(char**));
	i = 0;
	while (tmp)
	{
		env_path[i] = join_key_with_value(tmp);
		tmp = tmp->next;
		i++;
	}
	env_path[i] = NULL;
	_ = ft_sort_tab(env_path,len);
	i = 0;
	while (_[i])
	{
		ft_putstr_fd("declare -x ",1);
		ft_putstr_fd(_[i],1);
		write(1,"\n",1);
		i++;
	}
}

t_shell *create_node(char *args)
{
	t_shell *node;
	node = malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->key = extract_args(args,'K');
	node->value = extract_args(args,'V');
	node->next = NULL;
	return (node);
}

void add_back(t_shell **head,t_shell *last)
{
	t_shell	*tmp;
	if (*head == NULL)
		*head = last;
	else
	{	tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next  = last;
	}	
}
