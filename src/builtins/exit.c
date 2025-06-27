/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:05 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/22 09:25:42 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(int option, char **args, int *i, int *j)
{
	char *msg;
	msg = ": numeric argument required";
	if (option == 1)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
	}
	if (option == 2)
	{
		write(2, "exit: ", 6);
		write(2, &args[*i][*j], ft_strlen(args[*i]));
		write(2, msg, ft_strlen(msg));
	}
}

void	ft_exit(char **args)
{
	int	num;
	int	i;
	int	j;

	i = 1;
	if (!args[1])
		exit(EXIT_SUCCESS);
	while (args[i])
		i++;
	if (i > 2)
	{
		print_error(1, args, &i,&j);
		return ;
	}
	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '+' || args[i][j] == '-')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
			{
				print_error(2, args, &i, &j);
				exit(255);
			}
			j++;
		}
		i++;
	}
	num = ft_atoi(args[1]);
	exit(num);
}
