/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:58:08 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 18:13:14 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exit_error(int option, char **args)
{
	if (option == 1)
	{
		write(2, "exit\n", 5);
		write(1, "minishell: ", 12);
		write(2, "exit: too many arguments", 25);
		write(2, "\n", 1);
	}
	if (option == 2)
	{
		write(1, "minishell: ", 12);
		write(2, "exit: ", 6);
		write(2, args[1], ft_strlen(args[1]));
		ft_putstr_fd(": numeric argument required", 2);
		write(2, "\n", 1);
	}
	if (option == 3)
	{
		write(1, "minishell: ", 12);
		write(2, "exit: ", 6);
		ft_putstr_fd("numeric argument required: ", 2);
		write(2, args[1], ft_strlen(args[1]));
		write(2, "\n", 1);
	}
}

int	ft_pwd(char **args)
{
	char	pwd[1024];
	char	*msg;

	msg = "pwd: too many arguments";
	getcwd(pwd, sizeof(pwd));
	if (args[1])
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		g_exit_status = 1;
		return (g_exit_status);
	}
	ft_putendl_fd(pwd, 1);
	return (g_exit_status);
}
