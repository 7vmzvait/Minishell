/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:30:31 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 18:18:21 by haitaabe         ###   ########.fr       */
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
        if (!current)
        {
            current = new_cmd();
            if (!head)
                head = current;
        }

        if (!ft_strcmp(tokens[i], "|"))
        {
            current->next = new_cmd();
            current = current->next;
            i++;
        }
        else if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") ||
                 !ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<"))
        {
            handle_redir(current, tokens, &i);
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
