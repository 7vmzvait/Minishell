/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:46:47 by haitaabe          #+#    #+#             */
/*   Updated: 2025/04/30 16:16:23 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_types(char *token)
{
    if (ft_strncmp(token,"|", 1) == 0)
        return PIPE;
    else if (ft_strncmp(token, "<<", 2) == 0)
        return HEREDOC;
    else if (ft_strncmp(token, ">", 1) == 0)
        return OUT_FILE;
    else if (ft_strncmp(token, "<", 1) == 0)
        return IN_FILE;
    else if (ft_strncmp(token, ">>", 2) == 0)
        return APPANED;
    else 
        return WORD;
}

int main()
{
    char *cmd = "echo | test > test.txt | grep h";
    while (*cmd)
    {
        printf(" -> %d ->\n", check_types(cmd));
        cmd++;
    }
}