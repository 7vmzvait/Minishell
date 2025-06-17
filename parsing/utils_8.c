/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:30:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 13:02:21 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *parse_tokens(char **tokens)
{
    int i = 0;
    t_cmd *head = new_cmd_node();
    t_cmd *current = head;

    while (tokens[i])
    {
        if (tokens[i][0] == '|')
        {
            current->next = new_cmd_node();
            current = current->next;
            i++;
        }
        else if (tokens[i][0] == '<')
        {
            if (tokens[i + 1])
                set_infile(current, tokens[i], tokens[i + 1]);
            i += 2;
        }
        else if (tokens[i][0] == '>')
        {
            if (tokens[i + 1])
                set_outfile(current, tokens[i], tokens[i + 1]);
            i += 2;
        }
        else
        {
            add_arg_to_cmd(current, tokens[i]);
            i++;
        }
    }
    return head;
}
