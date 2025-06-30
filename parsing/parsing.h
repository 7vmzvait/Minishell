/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:43:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 18:09:55 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"


#define MAX_TOKENS 1024
// Token Types
typedef enum e_token_type
{
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    WORD
} t_token_type;

// Token Struc
typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// Command Struct
typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int fd;
    int append;
    int heredoc;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;


void print1(t_cmd *cmd);
// PARSING FUNCTIONS
t_cmd *parse_input(char *input); // entry point

int get_token_len(char *line, int i);
// TOKENIZER
char **tokenize(char *line); // array of strings (words/operators)
int is_space(int c);
int is_special(char c);
void skip_spaces(char *line, int *i);
t_token_type get_token_type(char *str);
char *extract_word(const char *input, int *i);
char *extract_special(const char *input, int *i);
char *extract_quoted(const char *input, int *i);

// COMMAND BUILDERS
t_cmd *new_cmd_node(void);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
void add_arg(char ***args, char *new_arg);
void add_arg_to_cmd(t_cmd *cmd, char *arg);

// REDIRECTION HANDLING
void handle_redir(t_cmd *cmd, t_token **token);
void set_infile(t_cmd *cmd, char *redir, char *file);
void set_outfile(t_cmd *cmd, char *redir, char *file);
// MEMORY UTILS
void free_tokens(char **tokens);
void free_command_list(t_cmd *cmds);
void free_cmds(t_cmd *head);

// SYNTAX CHECKING
int check_syntax_error(char **tokens);

void print_cmds(t_cmd *cmds);

// for tokens
t_token *new_token(t_token_type type, char *value);
void add_token(t_token **head, t_token *new_token);
void free_token_list(t_token *head);

// cmd builder 
t_cmd *new_cmd_node(void);
void add_arg_to_cmd(t_cmd *cmd, char *arg);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);

// for expand
char *expand_variables(const char *input, char **envp, int exit_status);

// to know the type of tokens 
t_token_type get_token_type(char *str);

t_cmd *parse_tokens(t_token *tokens);
t_cmd *parse_tokens1(char **tokens);
t_cmd *parse_input(char *input);
t_token *tokenize_input(char *str);


char *ft_itoa_custom(int n);
char *strjoin_and_free(char *s1,const  char *s2);
char *strjoin_and_free_char(char *s1, char c);
int is_valid_var_char(char c);
char *extract_var_name(const char *input, int *i);
#endif