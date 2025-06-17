/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:20:03 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 20:20:36 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_tokens(char **tokens)
{
    int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
