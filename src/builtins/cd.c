/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:42 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/18 18:37:26 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
char	updata_path(t_cmd *shell , char *parm,int len)
{
	int		j;
	int		size;
	char	*ptr;
	char	*ptr2;

	while (shell)
	{
		j = 0;
		while (shell->env[j])
		{
			if (ft_strncmp(shell->env[j],parm,len) == 0)
			{
				size = ft_strlen(shell->env[j]);
				ptr = malloc((size + 1) * sizeof(char));
				ft_strlcpy(ptr,shell->env[j],size+1);
				ptr2 = ft_substr(ptr,len,size);
				return (ptr2);
			}
			j++;
		}
		shell = shell->next;
	}
	return (NULL);
}
*/

void	cd(t_cmd *shell, char **args)
{
	char	cwd[1024];

	if (!args[1])
	{
		chdir(getenv("HOME"));
		return ;
	}
	else
		chdir(args[1]);
	if (ft_strncmp(args[1], "-", 1) == 0)
		chdir(getenv("OLDPWD"));
	getcwd(cwd, sizeof(cwd));
	(void)shell;
}
