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

void	print_error(int option, char **args)
{
	if (option == 1)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments", 25);
		write(2,"\n",1);
	}
	if (option == 2)
	{
		write(2, "exit: ", 6);
		write(2, args[1], ft_strlen(args[1]));
		ft_putstr_fd(": numeric argument required",2);
		write(2,"\n",1);
	}
	if (option == 3)
	{
		write(2, "exit: ", 6);
		ft_putstr_fd("numeric argument required: ",2);
		write(2, args[1], ft_strlen(args[1]));
		write(2,"\n",1);
	}
}
int is_valid_number(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i]== '+' || str[i] == '-')
			i++;
		if (!ft_isdigit(str[i]))
				return (1);
		i++;
	}
	return (0);
}

int is_big_number(const char *str)
{
	int i = 0;
	int sign = 1;
	long long result = 0;
	int digit;

	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
			return (1);
		if (sign == 1 && result > (LLONG_MAX - digit) / 10)
			return (1); 
		if (sign == -1 && result > (-(LLONG_MIN + digit)) / 10)
			return (1);
		result = result * 10 + digit;
		i++;
	}
	return (0);
}

int	ft_exit(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		write(1,"exit\n",6);
		g_exit_status = EXIT_SUCCESS;
		exit(g_exit_status);
	}
	while (args[i])
		i++;
	if (i > 2)
	{
		print_error(1, args);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (is_valid_number(args[1]))
	{
		print_error(2,args);
		g_exit_status = 255;
		return (g_exit_status);
	}
	if (is_big_number(args[1]))
	{
		print_error(3,args);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	write(1,"exit\n",6);
	g_exit_status = ft_atoi(args[1]);
	exit(g_exit_status);
}
