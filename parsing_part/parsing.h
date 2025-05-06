/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:53 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/06 17:34:41 by haitaabe         ###   ########.fr       */
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
    WORD,         // Any word or command
    PIPE,         // |
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    HEREDOC,      // <<
    VAR,          // $VARIABLE or $?
    SINGLE_QUOTE, // '...'
    DOUBLE_QUOTE  // "..."
} t_token_type;

typedef struct s_token
{
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;

#endif