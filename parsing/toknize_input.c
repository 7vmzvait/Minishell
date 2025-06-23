/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toknize_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:01:07 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/23 17:30:42 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *tokenize_input(char *str)
{
	int i = 0;
	t_token *tokens = NULL;

	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break;

		if (str[i] == '"' || str[i] == '\'')
		{
			char *val = get_quoted(str, &i);
			if (val)
				add_token(&tokens, WORD, val);
			else
				break;
		}
		else if (is_special(str[i]))
		{
			char *val = get_operator(str, &i);
			int dummy = 0;
			if (val)
				add_token(&tokens, get_token_type(val), val);
			else
				break;
		}
		else
		{
			char *val = get_word(str, &i);
			if (val)
				add_token(&tokens, WORD, val);
			else
				break;
		}
	}
	return tokens;
}
