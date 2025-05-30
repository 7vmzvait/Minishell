/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:12:10 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/18 18:10:52 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
#include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <string.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
    char **args;
    char **env;
    char *infile;
    char *outfile;
    int append;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;


void	minishell(t_cmd *cmd,char **env);
t_cmd 	*parse_commands(char *args);
void	print_cmd_list(t_cmd *cmd);
void	cd(t_cmd *shell, char **args);
void	ft_exit(char **args);
void	echo(char **args);
void	free_split(char **split_path);
int		open_file(char *file, int mode);
char	*get_next_line(int fd);
void	error(int mode);
void	exec(char *av, char **env);
#endif
