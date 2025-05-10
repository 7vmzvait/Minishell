/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:55 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/10 16:13:51 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_space(int check_s)
{
    return (check_s == 32 || (check_s >= 9 && check_s <= 13));
}

int Define_token_type(char *line)
{
    if (ft_strncmp(line, "|", 1) == 0)
        return PIPE;
    else if (ft_strncmp(line, ">>", 2) == 0)
        return REDIR_APPEND;
    else if (ft_strncmp(line, "<<", 2) == 0)
        return HEREDOC;
    else if (ft_strncmp(line, "<", 1) == 0)
        return REDIR_IN;
    else if (ft_strncmp(line, ">", 1) == 0)
        return REDIR_OUT;
    else if (ft_strncmp(line, "$", 1) == 0)
        return VAR;
    else if (line[0] == '"')
        return DOUBLE_QUOTE;
    else if (line[0] == '\'')
        return SINGLE_QUOTE;
    else
        return WORD;
}