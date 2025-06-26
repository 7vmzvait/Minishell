/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:45:42 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:56 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *tokenize_input(char *input)
{
    int i = 0;
    t_token *tokens = NULL;
    char *word;

    while (input[i])
    {
        if (is_space(input[i]))
            skip_spaces(input, &i);
        else if (is_special(input[i]))
        {
            word = extract_special(input, &i);
            add_token(&tokens, new_token(get_token_type(word), word));
        }
        else if (input[i] == '\'' || input[i] == '\"')
        {
            word = extract_quoted(input, &i);
            add_token(&tokens, new_token(WORD, word));
        }
        else
        {
            word = extract_word(input, &i);
            add_token(&tokens, new_token(WORD, word));
        }
    }
    return tokens;
}