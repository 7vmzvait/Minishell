/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:34:41 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/29 15:32:42 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>



int main(int argc,char **argv,char **env)
{
	(void)argc;
	(void)argv;
	

	t_cmd *cmd;
    t_context *ctx;
	//char **args;
	char *input;


	// char **args;
	cmd = malloc(sizeof(t_cmd));
    ctx = malloc (sizeof(t_context));
	ctx->env = env;
    t_shell *shell = NULL;
	add_node(&shell, env, NULL );
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		cmd = parse_input(input);
		execute_commands(cmd,ctx,&shell);
	}
}
