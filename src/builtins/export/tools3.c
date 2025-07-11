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

int	print_synatx_error(char *args)
{
	char	*msg;

	msg = ": not a valid identifier\n";
	write(2, "export: ", 8);
	write(2, args, ft_strlen(args));
	write(2, msg, ft_strlen(msg));
	return (0);
}

int	is_valid_export_syntax(char *args)
{
	int	i;

	if (!args || args[0] == '\0')
		return (print_synatx_error(args), 1);
	if (args[0] == '+' || args[0] == '=' || (!ft_isalpha(args[0])
			&& args[0] != '_'))
	{
		return (print_synatx_error(args), 1);
	}
	i = 1;
	while (args[i] && args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
		{
			print_synatx_error(args);
			return (1);
		}
		i++;
	}
	return (0);
}
