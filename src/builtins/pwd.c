/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:58:08 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/28 19:01:26 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int pwd(char **args,int fd)
{
	char pwd[1024];
	char *msg;

	msg = "pwd: too many arguments";
	getcwd(pwd,sizeof(pwd));
	if (args[1])
	{
		write(2,msg,ft_strlen(msg));
		write(2,"\n",1);
		return (1);
	}
	ft_putendl_fd(pwd,fd);
	return (0);
}


