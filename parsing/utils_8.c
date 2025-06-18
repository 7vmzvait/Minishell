/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:30:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 20:30:02 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *parse_tokens(char **tokens)
{
    t_cmd *head = init_command();
    t_cmd *current = head;
    int i = 0;

    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "<") == 0)
        {
            i++;
            current->infile = ft_strdup(tokens[i]);
            i++;
        }
        else if (ft_strcmp(tokens[i], ">") == 0)
        {
            i++;
            current->outfile = ft_strdup(tokens[i]);
            current->append = 0;
            i++;
        }
        else if (ft_strcmp(tokens[i], ">>") == 0)
        {
            i++;
            current->outfile = ft_strdup(tokens[i]);
            current->append = 1;
            i++;
        }
        else if (ft_strcmp(tokens[i], "|") == 0)
        {
            t_cmd *new_cmd = init_command();
            current->next = new_cmd;
            current = new_cmd;
            i++;
        }
        else
        {
            add_arg(current, tokens[i]);
            i++;
        }
    }
    return head;
}
