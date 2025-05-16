/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:12:10 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/16 11:07:34 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
#include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
	char **args;
	int infile;
	int outfile;
	int rediction;
	struct s_cmd *next;
}t_cmd;

void	free_split(char **split_path);
int		open_file(char *file, int mode);
char	*get_next_line(int fd);
void	error(int mode);
void	exec(char *av, char **env);
#endif
