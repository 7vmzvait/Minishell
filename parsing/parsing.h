/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:49:59 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/15 18:18:10 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;

#endif