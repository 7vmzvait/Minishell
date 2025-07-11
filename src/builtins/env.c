/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:55:07 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 17:50:13 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_create_env_line(t_shell *shell)
{
	int		len;
	int		i;
	int		j;
	char	*join;

	if (!shell->value)
		return (ft_strdup(shell->key));
	len = (ft_strlen(shell->key) + ft_strlen(shell->value));
	join = malloc((len + 2) * sizeof(char));
	i = -1;
	while (shell->key[++i])
		join[i] = shell->key[i];
	j = 0;
	join[i++] = '=';
	while (shell->value[j])
		join[i++] = shell->value[j++];
	join[i] = '\0';
	return (join);
}

void	display_env_list(t_env *env)
{
	t_shell	*current;
	int		counter;
	char	**env_var;

	counter = 0;
	current = env->env_list;
	while (current)
	{
		counter++;
		current = current->next;
	}
	env_var = malloc((counter + 1) * sizeof(char *));
	if (!env_var)
		return ;
	current = env->env_list;
	counter = 0;
	while (current && current->value)
	{
		env_var[counter] = ft_create_env_line(current);
		ft_putendl_fd(env_var[counter], 1);
		current = current->next;
		counter++;
	}
	free_env(env_var);
}

int	ft_env(t_env *env, t_shell *shell, char **args)
{
	char	*msg;

	(void)shell;
	msg = ": No such file or directory";
	if (!getenv_path(env))
	{
		print_error2("env", msg);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (!args[0])
		return (1);
	if (args[1])
	{
		write(2, "env: ", 5);
		write(2, args[1], ft_strlen(args[1]));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		g_exit_status = 1;
		return (g_exit_status);
	}
	display_env_list(env);
	return (g_exit_status);
}
