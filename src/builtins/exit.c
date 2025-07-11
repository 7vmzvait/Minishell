/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:05 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 18:08:10 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_big_number(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	int			digit;

	i = -1;
	sign = 1;
	result = 0;
	if (str[++i] == '+' || str[++i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
	}
	while (str[++i])
	{
		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
			return (1);
		if (sign == 1 && result > (LLONG_MAX - digit) / 10)
			return (1);
		if (sign == -1 && result > (-(LLONG_MIN + digit)) / 10)
			return (1);
		result = result * 10 + digit;
	}
	return (0);
}

int	too_many_args_hendler(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
	{
		print_exit_error(1, cmd->args);
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}

int	helper_fuc(t_cmd *cmd)
{
	if (is_valid_number(cmd->args[1]))
	{
		print_exit_error(2, cmd->args);
		g_exit_status = 255;
		return (g_exit_status);
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		write(1, "exit\n", 6);
		free_cmds(cmd);
		g_exit_status = EXIT_SUCCESS;
		exit(g_exit_status);
	}
	if (helper_fuc(cmd) == 255)
		return (g_exit_status);
	if (too_many_args_hendler(cmd) == 1)
		return (g_exit_status);
	if (is_big_number(cmd->args[1]) != 0)
	{
		print_exit_error(3, cmd->args);
		g_exit_status = 2;
		free_cmds(cmd);
		exit(g_exit_status);
	}
	write(1, "exit\n", 6);
	g_exit_status = ft_atoi(cmd->args[1]);
	free_cmds(cmd);
	exit(g_exit_status);
}
