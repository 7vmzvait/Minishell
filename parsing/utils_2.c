/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:52:23 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/13 17:40:37 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type get_token_type(char *str)
{
    if (!str)
        return WORD;

    if (strcmp(str, "|") == 0)
        return PIPE;
    else if (strcmp(str, "<") == 0)
        return REDIR_IN;
    else if (strcmp(str, ">") == 0)
        return REDIR_OUT;
    else if (strcmp(str, ">>") == 0)
        return APPEND;
    else if (strcmp(str, "<<") == 0)
        return HEREDOC;
    else
        return WORD;
}

t_cmd *init_cmd_node(void)
{
    t_cmd *node = malloc(sizeof(t_cmd));
    if (!node)
        return NULL;

    node->args = NULL;
    node->infile = NULL;
    node->outfile = NULL;
    node->append = 0;
    node->next = NULL;
    return node;
}

void add_arg(char ***args, char *new_arg)
{
    int count = 0;
    char **new_args;

    if (*args)
    {
        while ((*args)[count])
            count++;
    }

    // Allocate new array: existing + new + NULL
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return;

    // Copy old args
    int i = 0;
    while (i < count)
    {
        new_args[i] = (*args)[i];
        i++;
    }

    // Add new one
    new_args[count] = ft_strdup(new_arg);
    new_args[count + 1] = NULL;

    // Free only the old array (not strings inside)
    if (*args)
        free(*args);

    // Update pointer
    *args = new_args;
}

void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
    if (!*list)
        *list = new_cmd;
    else
    {
        t_cmd *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}