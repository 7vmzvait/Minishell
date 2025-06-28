/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:34:41 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/23 15:40:12 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>

void print2(t_cmd *cmd)
{
    int i;
    while (cmd)
    {
        printf("Command: ");
        for (i = 0; cmd->args && cmd->args[i]; i++)
            printf("[%s] ", cmd->args[i]);
        printf("\n");
        cmd = cmd->next;
    }
}

t_cmd  *create_command(char **cmd)
{
	t_cmd *node = malloc(sizeof(t_cmd));
	
	if (node == NULL)
		return (NULL);
	node->args = cmd;
	node->next = NULL;
	return (node);
}

t_cmd *parse_commands(char *args)
{
	int i;
	char **split_pip;
	t_cmd *current = NULL;
	t_cmd *head = NULL;
	t_cmd *node;

	i = 0;
	split_pip = ft_split(args,'|');
	while (split_pip[i])
	{
		node = create_command(&split_pip[i]);
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		i++;
	}
	return (head);
}

int main(int argc,char **argv,char **env)
{
	(void)argc;
	(void)argv;
	

	t_cmd *cmd;
    t_context *ctx;
	char *input;

	// char **args;
	cmd = malloc(sizeof(t_cmd));
    ctx = malloc (sizeof(t_context));
    ctx->env = env;
	while (1)
	{
		input = readline("> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
        cmd = parse_input(input);
		// print_cmds(cmd);
		execute_commands(cmd,ctx);
	}
}