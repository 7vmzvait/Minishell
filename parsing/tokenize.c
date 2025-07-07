/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:45:42 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:25:47 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parsing.h"

t_token	*tokenize_input(char *input)
{
	int i = 0;
	t_token *tokens = NULL;

<<<<<<< HEAD
	while (input[i])
	{
		if (is_space(input[i]))
			skip_spaces(input, &i);
		else if (is_special(input[i]))
		{
			char *word = extract_special(input, &i);
			add_token(&tokens, new_token(get_token_type(word), word));
		}
		else
		{
			char token_buf[4096] = {0};
			int has_token = 0;

			// Collect adjacent quoted/unquoted segments as one token
			while (input[i] && !is_space(input[i]) && !is_special(input[i]))
			{
				if (input[i] == '\'' || input[i] == '\"')
				{
					int is_single = 0;
					char *quoted = extract_quoted(input, &i, &is_single);
						// update your extract_quoted to support this
					if (!quoted)
					{
						print_error2("bash: syntax error near unexpected token",
							"`newline'");
						free_token_list(tokens);
						return (NULL);
					}
					strcat(token_buf, quoted);
					free(quoted);
					has_token = 1;
				}
				else
				{
					char *word = extract_word(input, &i);
					strcat(token_buf, word);
					free(word);
					has_token = 1;
				}
			}
			if (has_token)
				add_token(&tokens, new_token(WORD, strdup(token_buf)));
		}
	}
	return (tokens);
=======
    while (input[i])
    {
        if (is_space(input[i]))
            skip_spaces(input, &i);
        else if (is_special(input[i]))
        {
            char *word = extract_special(input, &i);
            add_token(&tokens, new_token(get_token_type(word), word));
        }
        else
        {
            char token_buf[4096] = {0};
            int has_token = 0;
            while (input[i] && !is_space(input[i]) && !is_special(input[i]))
            {
                if (input[i] == '\'' || input[i] == '\"')
                {
                    int is_single = 0;
                    char *quoted = extract_quoted(input, &i, &is_single);
                    if (!quoted)
                    {
                        print_error2("bash: syntax error near unexpected token", "`newline'");
                        free_token_list(tokens);
                        return NULL;
                    }
                    ft_strcat(token_buf, quoted);
                    free(quoted);
                    has_token = 1;
                }
                else
                {
                    char *word = extract_word(input, &i);
                    ft_strcat(token_buf, word);
                    free(word);
                    has_token = 1;
                }
            }
            if (has_token)
                add_token(&tokens, new_token(WORD, strdup(token_buf)));
        }
    }
    return tokens;
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
}