/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:17:29 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:18:46 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_cmds(t_cmd *cmds)
{
    int i;

    while (cmds)
    {
        printf("----- Command -----\n");

        if (cmds->args)
        {
            i = 0;
            while (cmds->args[i])
            {
                printf("  Arg[%d]: %s\n", i, cmds->args[i]);
                i++;
            }
        }
        else
        {
            printf("  No arguments.\n");
        }

        printf("  Infile  : %s\n", cmds->infile ? cmds->infile : "NULL");
        printf("  Outfile : %s\n", cmds->outfile ? cmds->outfile : "NULL");
        printf("  Append  : %d\n", cmds->append);
        printf("  Heredoc : %d\n", cmds->heredoc);
        printf("  Pipe to next: %d\n", cmds->pipe_to_next);

        cmds = cmds->next;
    }
}
