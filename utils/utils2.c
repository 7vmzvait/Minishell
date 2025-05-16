/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:08:08 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/15 09:11:36 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_split(char **split_path)
{
	int	i;

	i = 0;
	if (!split_path)
		return ;
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
}

void	error(int mode)
{
	if (mode == -1)
	{
		perror("\033[31mError");
		exit(EXIT_FAILURE);
	}
	if (mode == 1)
		exit(EXIT_SUCCESS);
	if (mode == 2)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... file2\n", 41);
		exit(EXIT_FAILURE);
	}
	if (mode == 3)
	{
		write(2, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... file\n", 50);
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *file, int mode)
{
	int	file_dec;

	if (mode == 0)
		file_dec = open(file, O_RDONLY);
	if (mode == 1)
		file_dec = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mode == 2)
		file_dec = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_dec == -1)
		return (0);
	return (file_dec);
}
