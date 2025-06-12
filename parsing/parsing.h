/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:49:59 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/11 11:02:29 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../libft/libft.h"

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_REDIR_HERE_DOC
} t_token_type;

typedef struct s_token
{
    char *value;          // The actual word or symbol (like "|", "<", ">>")
    t_token_type type;    // The token type
    struct s_token *next; // For linked list of tokens
} t_token;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    int pipe_to_next; // 0 or 1
    struct s_cmd *next;
} t_cmd;

t_token *tokenize_input(char *line);
// Adds a new token to the linked list
void add_token(t_token **head, int type, char *value);

// Returns 1 if character is |, <, >; 0 otherwise
int is_special_char(char c);

// to check spaces
int is_space(int check_s);

// Extracts a normal word (not in quotes)
char *get_word(char *line, int *i);

// just to use it instead of ft_strdup cuz we need the len of the word
char *ft_strdup_range(char *str, int start, int len);
// Extracts quoted word (supports single and double quotes)
char *get_quoted_word(char *line, int *i);

// Gets the token type for <, >, <<, >>
int get_token_type(char *line, int *i);

t_cmd *parse_tokens(t_token *token_list);
int tokens(char *line);
t_cmd *create_cmd(void);
void add_arg_to_cmd(t_cmd *cmd, char *arg);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
#endif
