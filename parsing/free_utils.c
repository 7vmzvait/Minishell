/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:47:47 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 17:09:01 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_command_list(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;

    while (cmds)
    {
        tmp = cmds;
        cmds = cmds->next;

        if (tmp->args)
        {
            i = 0;
            while (tmp->args[i])
            {
                free(tmp->args[i]);
                i++;
            }
            free(tmp->args);
        }
        free(tmp->infile);
        free(tmp->outfile);
        free(tmp);
    }
}