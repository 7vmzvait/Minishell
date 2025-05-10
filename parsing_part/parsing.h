/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:53 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/10 15:07:56 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <stdlib.h>

typedef enum e_token_type
{
    PIPE,         // |
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    HEREDOC,      // <<
    VAR,          // $VARIABLE or $?
    DOUBLE_QUOTE, // "..."
    SINGLE_QUOTE, // '...'
    WORD          // Any word or command
} t_token_type;

typedef struct s_token
{
    char *value;       // like "echo", ">", "file.txt"
    t_token_type type; // from your enum
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
    char **args;        // command + arguments (["ls", "-l", NULL])
    char *infile;       // for '<'
    char *outfile;      // for '>' or '>>'
    int append;         // 1 if >>, 0 if >
    int heredoc;        // 1 if << used
    char *limiter;      // for heredoc: the END word
    struct s_cmd *next; // for pipe: next command
} t_cmd;

#endif