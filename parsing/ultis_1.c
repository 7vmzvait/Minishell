/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultis_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:49:56 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/21 16:22:49 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_space(int check_s)
{
    return (check_s == 32 || (check_s >= 9 && check_s <= 13));
}
int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>');
}
void free_command_list(t_cmd *cmds)
{
    t_cmd *tmp;
    int j;

    while (cmds)
    {
        if (cmds->args)
        {
            j = 0;
            while (cmds->args[j])
            {
                free(cmds->args[j]);
                j++;
            }
            free(cmds->args);
        }
        if (cmds->infile)
            free(cmds->infile);
        if (cmds->outfile)
            free(cmds->outfile);
        tmp = cmds;
        cmds = cmds->next;
        free(tmp);
    }
}
