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

char	**ft_sort_tab(char **tab, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
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

char	*join_key_with_value(t_shell *shell)
{
	int		len;
	int		i;
	int		j;
	char	*join;

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

int	count_env_length(t_env *env)
{
	t_shell	*tmp;
	int		len;

	tmp = env->env_list;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**prepare_env_array(t_env *env)
{
	t_shell	*tmp;
	int		len;
	int		i;
	char	**env_path;

	len = count_env_length(env);
	env_path = malloc((len + 1) * sizeof(char **));
	if (!env_path)
		return (NULL);
	tmp = env->env_list;
	i = 0;
	while (tmp)
	{
		env_path[i] = join_key_with_value(tmp);
		tmp = tmp->next;
		i++;
	}
	env_path[i] = NULL;
	return (env_path);
}

void	print_export(t_env *env)
{
	char	**env_path;
	char	**sorted_env;
	int		i;

	env_path = prepare_env_array(env);
	if (!env_path)
		return ;
	sorted_env = ft_sort_tab(env_path, count_env_length(env));
	i = 0;
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted_env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	free_env(env_path);
}
