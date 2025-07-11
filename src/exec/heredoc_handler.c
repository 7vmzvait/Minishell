/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:35:05 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:35:09 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child(char *del, int *pipfd)
{
	char	*line;

	close(pipfd[0]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, del, ft_strlen(del)) == 0 && ft_strlen(line)
			- 1 == ft_strlen(del))
		{
			free(line);
			close(pipfd[1]);
			get_next_line(-1);
			exit(g_exit_status);
		}
		write(pipfd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char *del)
{
	int	pipfd[2];
	int	pid;

	if (pipe(pipfd) == -1)
		perror("Error: ");
	pid = fork();
	if (pid == -1)
		perror("Error: ");
	if (pid == 0)
		child(del, pipfd);
	else
	{
		close(pipfd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
