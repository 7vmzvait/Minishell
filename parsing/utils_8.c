/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:30:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/13 17:37:45 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *parse_tokens(char **tokens)
{
    int i = 0;
    t_cmd *head = NULL;
    t_cmd *current = NULL;

    while (tokens[i])
    {
        t_cmd *node = init_cmd_node();

        if (!head)
            head = node;
        else
            current->next = node;

        current = node;

        while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
        {
            if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
            {
                current->infile = ft_strdup(tokens[i + 1]);
                i += 2;
            }
            else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
            {
                current->outfile = ft_strdup(tokens[i + 1]);
                current->append = 1;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], ">") == 0 && tokens[i + 1])
            {
                current->outfile = ft_strdup(tokens[i + 1]);
                current->append = 0;
                i += 2;
            }
            else
            {
                add_arg(&current->args, tokens[i]);
                i++;
            }
        }

        if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
            i++;
    }

    return head;
}
