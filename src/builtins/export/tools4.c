/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:21:26 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 12:21:31 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void  update(t_shell **shell,char *args)
{
	t_shell	*tmp;
	char 	*key;
	char	*value;
	
	key = extract_args(args,'K');
	value = extract_args(args,'V');
	tmp = *shell;
	while (tmp)
	{
		if(ft_strncmp(tmp->key,key,ft_strlen(key)) == 0)
		{
			free(tmp->key);
			free(tmp->value);
			tmp->key = key;
			tmp->value = value;
			return;
		}
		tmp = tmp->next;
	}
	free(key);
	free(value);
	add_back(shell,create_node(args));
}

void join_key(t_shell **shell ,char *args)
{
	t_shell *tmp;
	char	*join;
	char 	*key;
	char	*value;

	key = extract_keys(args,'K');
	value = extract_keys(args,'V');
	tmp = *shell;
	while (tmp)
	{
		if (ft_strncmp(tmp->key,key,ft_strlen(key)) == 0)
		{
			join = ft_strjoin(tmp->value,value);
			tmp->value = join;
			return;
		}
		tmp = tmp->next;
	}
	free(key);
	free(value);
}

void add_node(t_shell **shell,char **env ,char *last)
{
	int	i;

	// t_shell *tmp;/
	//tmp = *shell;
	i = 0;
	if (!last)
	{	
		while (env[i])
		{
			add_back(shell,create_node(env[i]));
			i++;
		}
	}
	else
		update(shell,last);
}

char **clean_str(char *str)
{
	int	i;
	int 	j;
	int 	len;
	char *rm;
	char **clean;

	len = 0;
	while (str[len])
		len++;
	rm = malloc((len + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		rm[j] =  str[i];
		j++;
		i++;
	}
	clean = malloc((j + 2) * sizeof(char*));
	clean[0] = rm;
	clean[1] = NULL;
	return (clean);
}


