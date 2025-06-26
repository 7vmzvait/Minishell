/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:41 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:01:52 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *extract_special(const char *input, int *i)
{
    if (input[*i] == '>' && input[*i + 1] == '>')
    {
        (*i) += 2;
        return ft_strdup(">>");
    }
    else if (input[*i] == '<' && input[*i + 1] == '<')
    {
        (*i) += 2;
        return ft_strdup("<<");
    }
    else
    {
        char op[2] = { input[*i], '\0' };
        (*i)++;
        return ft_strdup(op);
    }
}