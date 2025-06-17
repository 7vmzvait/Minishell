/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:21:00 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 18:21:10 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_cmds(t_cmd *head)
{
    t_cmd *tmp;
    int i;

    while (head)
    {
        tmp = head->next;

        // Free all args strings
        if (head->args)
        {
            i = 0;
            while (head->args[i])
            {
                free(head->args[i]);
                i++;
            }
            free(head->args);
        }

        // Free infile and outfile
        if (head->infile)
            free(head->infile);
        if (head->outfile)
            free(head->outfile);

        // Free the command node itself
        free(head);

        head = tmp;
    }
}
