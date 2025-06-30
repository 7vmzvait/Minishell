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

int path_len(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
	
}
