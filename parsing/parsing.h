/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:43:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 17:43:14 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../libft/libft.h"

#define MAX_TOKENS 1024

typedef enum e_token_type
{
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    WORD
} t_token_type;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    int heredoc;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

t_cmd *parse_tokens(char **tokens);
t_token_type get_token_type(char *str);
t_cmd *new_cmd_node(void);
void add_arg(char ***args, char *new_arg);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
char **tokenize(char *line);
int is_space(int check_s);
int is_special(char c);
void skip_spaces(char *line, int *i);
int get_token_len(char *line, int i);
int ft_strcmp(const char *s1, const char *s2);
t_cmd *parse_input(char *input);
char *extract_word(const char *input, int *i);
char *extract_special(const char *input, int *i);
char *extract_quoted(const char *input, int *i);
void add_arg_to_cmd(t_cmd *cmd, char *arg);
void set_infile(t_cmd *cmd, char *redir, char *file);
void set_outfile(t_cmd *cmd, char *redir, char *file);
char **tokenizer(const char *line);
char *get_word(const char *line, int *i);
char *get_quoted_word(const char *line, int *i);
char *get_special_token(const char *line, int *i);
void handle_redir(t_cmd *cmd, char **tokens, int *i);
t_token *tokenize_input(char *str);
void free_tokens(char **tokens);
void free_cmds(t_cmd *head);
void free_command_list(t_cmd *cmds);

int check_syntax_error(char **tokens);

char *expand_variables(const char *input, char **envp);

int is_valid_identifier(const char *str);

void print_syntax_error(const char *msg);

#endif
