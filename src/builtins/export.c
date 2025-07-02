/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:38:08 by eazmir            #+#    #+#             **   Updated: 2025/05/26 15:46:00 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char  *extract_args(char *args,char opt)
{
	char	*eq;
	char	*key;
	char	*value;
	int	len;
	
	eq = ft_strchr(args,'=');
	len = eq - args; 
	key = ft_substr(args,0,len);
	if (!key)
	{
		free(key);
		return(NULL);
	}
	if (!eq && opt != 'V')
		return (ft_strdup(key));
	else if (!eq && opt == 'V')
		return (NULL);
	value = ft_strdup(eq + 1);
	if (!value)
	{
		free(value);
		return (NULL);
	}        
	if (opt == 'V')
		return (value);
	if (opt == 'K')
		return (key);
	return (NULL);
}

char  *extract_keys(char *args,char opt)
{
	char	*eq;
	char	*key;
	char	*value;
	int	len;
	
	
	eq = ft_strchr(args,'+');
	len = eq - args;
	key = ft_substr(args,0,len);
	if (!key)
	{
		free(key);
		return(NULL);
	}
	value = ft_strdup(eq + 2);
	if (!value)
	{
		free(value);
		return (NULL);
	}
	if (opt == 'V')
		return (value);
	if (opt == 'K')
		return (key);
	return (NULL);
}

 
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


int path_len(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
	
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


void	printList(t_env *env)
{	
	t_shell *tmp;
	int 	len;
	int	i;
	char 	**env_path;
	char	**_;
	
	tmp = env->env_list;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	tmp = env->env_list;
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

void  update(t_shell **shell,char *args,t_env *env)
{
	t_shell	*tmp;
	char 	*key;
	char	*value;
	(void)shell;
	key = extract_args(args,'K');
	value = extract_args(args,'V');
	tmp = env->env_list;
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
	add_back(&env->env_list,create_node(args));
}

void join_key(t_shell **shell ,char *args,t_env *env)
{
	(void)shell;
	t_shell *tmp;
	char	*join;
	char 	*key;
	char	*value;

	key = extract_keys(args,'K');
	value = extract_keys(args,'V');
	tmp = env->env_list;
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

void add_node(t_shell **shell,char *last,t_env *env)
{
	if (!last)
	{	
		return ;
	}
	else
		update(shell,last,env);
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

int ft_export1(t_shell **shell,char **args,t_env *env)
{
	int	i;
	char	*plus;
	char	*equal;
	char	**cleaned;

	if (!args[0])
		return (0);
	if (!args[1])
	{
		printList(env);
		return (0);
	}
	if(is_valid_export_syntax(args[1]) != 0)
		return (0);
	cleaned = clean_str(args[1]);
	i = 0;
	while (cleaned[i])
	{
		plus = ft_strchr(cleaned[i],'+');
		equal = ft_strchr(cleaned[i],'=');
		if (plus && equal)
		{
			if (plus + 1 == equal)
				join_key(shell,cleaned[i],env);
			else
				add_node(shell,cleaned[i],env);
		}
		else
			add_node(shell,cleaned[i],env);
		i++;
	}
	return (0);

}
