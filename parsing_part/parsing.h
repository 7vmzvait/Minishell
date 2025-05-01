/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:45:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/01 15:12:36 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "../libft/libft.h"

enum TOKENS
{
    PIPE,
    IN_FILE,
    OUT_FILE,
    APPANED,
    HEREDOC,
    WORD
};

typedef struct s_command
{
    char **cmd;
    int in_file;
    int out_file;
    int appaned;
    int next_pipe;
} t_command;

typedef struct s_word
{
    char *value;
    t_command *cmd;
    struct s_word *next;
} t_word;

int check_is_space(int check_s);
int skip_spaces(char *str, int i);
int skip_quotes(char *str, int i);
char **tokenize(char *line);
#endif