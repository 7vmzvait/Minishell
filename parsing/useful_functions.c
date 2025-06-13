/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:32:26 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/13 17:42:35 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    return (s1[i] - s2[i]);
}
t_cmd *parse_input(char *input)
{
    char **tokens;
    t_cmd *cmd_list;

    tokens = tokenize(input);        // step 1
    if (!check_syntax(tokens))      // step 3
        return NULL;
    expand_tokens(tokens);          // step 4
    cmd_list = parse_tokens(tokens);
    free_tokens(tokens);
    return cmd_list;
}
