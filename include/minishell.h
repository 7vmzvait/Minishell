/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:46 by eazmir            #+#    #+#             */
/*   Updated: 2025/05/28 19:00:49 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include  "../parsing/parsing.h"

typedef struct s_context
{
    int prev_pipe;
    int last_pid;
    char **env;
    int fdpipe[2];
    pid_t pids;
}t_context;

typedef struct s_shell
{
	char *value;
 	char *key;
	char *env;
	struct s_shell *next;
}t_shell;


// typedef struct s_cmd
// {
//     char **args;
//     char *infile;
//     char *outfile;
//     int heredoc;
//     int append;
//     int pipe_to_next;
//     struct s_cmd *next;
// } t_cmd;

char  *extract_args(char *args,char opt);
void join_key(t_shell **shell ,char *args);
void add_back(t_shell **head,t_shell *last);
char **clean_str(char *str);
int path_len(char **tab);
void	printList(t_shell **shell);
t_shell *create_node(char *args);
char   **ft_sort_tab(char **tab,int len);
char *join_key_with_value(t_shell *shell);
int is_valid_export_syntax(char *args);
char  *extract_keys(char *args,char opt);
void	add_node(t_shell **shell,char **env,char *args);
void handle_redir1(t_cmd *cmd, char **tokens);
int is_redir(char *tokens);
int     execute_commands(t_cmd *cmd,t_context *ctx);
void    redirection(t_cmd *cmd);
void	cd(t_shell **shell, char **args);
void	ft_exit(char **args);
void	echo(char **args);
int	    ft_env(t_shell **shell,char **args,int fd);
int	    pwd(char **args,int fd);
int	    unset(t_shell **shell,char **args);
void	printList(t_shell **node);
void	ft_export(t_shell **shell,char **env,char **args);
char	**get_env(t_shell *shell);
void	free_split(char **split_path);
int		open_file(char *file, int mode);
char	*get_next_line(int fd);
void	error(int mode);
void	exec(char **cmd, char **env);
#endif

