/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:55:07 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/28 13:21:10 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *create_env_line(t_shell *shell)
{
	
	char *join;
	int	len;
	int	i;
	int 	j;

	len = ft_strlen(shell->key) + ft_strlen(shell->value);
	join = malloc((len + 2) * sizeof(char));
	
	i = -1;
	j = 0;
	while (shell->key && shell->key[++i])
		join[i] = shell->key[i];
	join[i++] = '=';
	while (shell->value && shell->value[j])
		join[i++] = shell->value[j++];
	join[i] = '\0';
	return (join);	
}

int  ft_env(t_shell **shell,char **args,int fd)
{
	t_shell *tmp;
	char	*env_path;
	char	*msg;

	tmp = *shell;
	msg = ": No such file or directory";
	if (!args[0])
		return(1);
	
	if (args[1])
	{
		write(2,"env: ",5);
		write(2,args[1],ft_strlen(args[1]));
		write(2,msg,ft_strlen(msg));
		write(2,"\n",1);
		return (1);
	}
	while (tmp)
	{
		env_path = create_env_line(tmp);
		write(fd,env_path,ft_strlen(env_path));
		write(fd,"\n",1);
		free(env_path);
		tmp = tmp->next;
	}
	return (1);
}
