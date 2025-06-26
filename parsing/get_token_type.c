/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:00:51 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:30:12 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type get_token_type(char *str)
{
    if (!str)
        return WORD;
    if (ft_strcmp(str, "|") == 0)
        return PIPE;
    if (ft_strcmp(str, "<") == 0)
        return REDIR_IN;
    if (ft_strcmp(str, ">") == 0)
        return REDIR_OUT;
    if (ft_strcmp(str, ">>") == 0)
        return APPEND;
    if (ft_strcmp(str, "<<") == 0)
        return HEREDOC;
    return WORD;
}