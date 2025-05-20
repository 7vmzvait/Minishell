/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:07 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/19 14:31:15 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void print_cmd_list(t_cmd *cmd)
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

int	pipex_bonus(char **av, char **env)
{
	int	pid;
	int	pipfd[2];

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		exec(av[0], env);
		//return (0);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipfd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		close(pipfd[0]);
		return (pid);
	}
}

void	minishell(t_cmd *cmd,char **env)
{
	int index;
	int num_child;
	int child_pids[1024];

	t_cmd *tmp;
	tmp = cmd;
	num_child = 0;
	//while (1)
	//{
		while (tmp->next)
		{
			child_pids[num_child++] = pipex_bonus(tmp->args, env);
			tmp = tmp->next;
		}
		child_pids[num_child] = fork();
		if (child_pids[num_child] == 0)
		{
			//dup2(1,STDOUT_FILENO);
			exec(tmp->args[0], env);
		}
		else
			num_child++;
		index = 0;
		while (index < num_child)
		{
			waitpid(child_pids[index], NULL, 0);
			index++;
		}
	//}
}
