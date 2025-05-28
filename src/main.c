/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:47 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/20 18:29:39 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **split_input(char *token)
{
	char **split;
	char **ptr;
	int i;
	split = ft_split(token, ' ');
	i = 0;
	while (split[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	i = 0;
	while (split[i])
	{
		ptr[i] = ft_strdup(split[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	char *input;
	t_cmd *cmd;
	char **args;
	cmd = malloc(sizeof(t_cmd));
	cmd->env = env;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		args = split_input(input);
		if (args[0] && ft_strncmp(args[0], "exit", 6) == 0)
		{
			ft_exit(args);
		}
		else
		{
			cmd = parse_commands(input);
			print_cmd_list(cmd);
			if (cmd)
				minishell(cmd, env);
		}
		// free(input);
	}
}
