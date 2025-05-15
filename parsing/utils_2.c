/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:52:23 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/15 18:58:58 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int simplify_token(char *line)
{
    if (ft_strncmp(line, "|", 1) == 0)
        return PIPE;
    else if (ft_strncmp(line, "<", 1) == 0)
        return REDIR_IN;
    else if (ft_strncmp(line, ">", 1) == 0)
        return REDIR_IN;
    else if (ft_strncmp(line, ">>", 2) == 0)
        return APPEND;
    else if (ft_strncmp(line, "<<", 2) == 0)
        return HEREDOC;
    else
        WORD;
}