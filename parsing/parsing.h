/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:49:59 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/15 18:21:56 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
} t_token_type;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

#endif