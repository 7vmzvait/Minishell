/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:15:32 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 17:18:20 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

int main(void)
{
    char *input = "echo hello > file.txt";

    t_token *tokens = tokenize_input(input);
    if (!tokens)
    {
        printf("Tokenizing failed.\n");
        return (1);
    }
    if (check_syntax_error(tokens))
    {
        free_tokens(tokens);
        return (1);
    }
    t_cmd *cmds = parse_tokens(tokens);

    free_cmds(cmds);
    free_tokens(tokens);

    return (0);
}
