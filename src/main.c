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
//char prompt_shell(char )

// Also, 'export' does not handle multiple values properly.
// It doesn't handle cases like: TEST="hello", then later: export TEST="Hello world".
// It should update TEST to the new value "Hello world", but it doesn't.


int g_exit_status = 0; 

t_env *init_env(char **env)
{
	int i;
	t_env *env_var;
	t_shell *new_node;
	env_var = malloc(sizeof(t_env));
	env_var->env_list = NULL;
	i = 0;
	while (env[i])
	{
		new_node = create_node(env[i]);
		add_back(&env_var->env_list,new_node);
		i++;
	}
	return (env_var);
}
void sigquit_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("core dumped",1);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}
void sigint_handler(int sig)
{
	(void)sig;
	write(1,"\n",1);
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int argc,char **argv,char **env)
{
	(void)argc;
	(void)argv;
	

	t_cmd *cmd;
    t_context *ctx;
	t_shell *shell;
	t_env *env_var;
	char *input;

	cmd = malloc(sizeof(t_cmd));
    ctx = malloc (sizeof(t_context));
	shell = malloc(sizeof(t_shell));
	env_var = init_env(env);
	signal(SIGINT,sigint_handler);
	signal(SIGQUIT,sigquit_handler);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break;
		if (*input)
		 	add_history(input);
		cmd = parse_input(input,env_var);
		execute_commands(cmd,ctx,shell,env_var);
	}
}
