/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:53:18 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 17:54:13 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	free_key2(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

char	*parse_key_value2(char *args, char **key, char **value)
{
	char	*eq;
	int		len;

	eq = ft_strchr(args, '+');
	if (eq)
	{
		len = eq - args;
		*key = ft_substr(args, 0, len);
		if (!*key)
		{
			free(*key);
			return (NULL);
		}
		*value = ft_strdup(eq + 1);
		if (!*value)
			return (free_key2(*key, *value), NULL);
	}
	else
	{
		*key = ft_strdup(args);
		*value = NULL;
	}
	return (eq);
}

char	*handle_extraction_option2(char *key, char *value, char opt)
{
	if (!value && opt != 'V')
		return (ft_strdup(key));
	else if (!value && opt == 'V')
		return (NULL);
	if (opt == 'V')
	{
		free(key);
		return (value);
	}
	if (opt == 'K')
	{
		free(value);
		return (key);
	}
	free(key);
	free(value);
	return (NULL);
}

char	*extract_keys(char *args, char opt)
{
	char	*key;
	char	*value;
	char	*eq;

	eq = parse_key_value2(args, &key, &value);
	if (!key)
		return (NULL);
	return (handle_extraction_option2(key, value, opt));
}
