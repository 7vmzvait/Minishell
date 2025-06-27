/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:18:38 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 12:18:41 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int is_valid_export_syntax(char *args)
{
	int		i;
	char	*msg = ": not a valid identifier\n";

	if (!args || args[0] == '\0')
		return (write(2, "export: ''", 10), write(2, msg, ft_strlen(msg)), 1);

	if (args[0] == '+' || args[0] == '=' || (!ft_isalpha(args[0]) && args[0] != '_'))
	{
		write(2, "export: ", 8);
		write(2, args, ft_strlen(args));
		write(2, msg, ft_strlen(msg));
		return (1);
	}

	i = 1;
	while (args[i] && args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
		{
			write(2, "export: ", 8);
			write(2, args, ft_strlen(args));
			write(2, msg, ft_strlen(msg));
			return (1);
		}
		i++;
	}
	return (0);
}



char   **ft_sort_tab(char **tab,int len)
{
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(tab[i],tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}


char *join_key_with_value(t_shell *shell)
{
	int len;
	int i;
	int j;
	char *join;

	if (!shell->value)
		return (ft_strdup(shell->key));
	len = (ft_strlen(shell->key) + ft_strlen(shell->value));
	join = malloc((len + 4) * sizeof(char));	
	i = -1;
	while (shell->key[++i])
		join[i] = shell->key[i];
	j = 0;
	join[i++] = '=';
	join[i++] = '"';
	while (shell->value[j])
		join[i++] = shell->value[j++];
	join[i++] = '"';
	join[i] = '\0';
	return (join);
}
