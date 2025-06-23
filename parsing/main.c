/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:15:32 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/21 16:15:34 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(void)
{
	char *input = "echo \"hello world\" > out.txt | cat";
	t_token *tokens = tokenize_input(input);

	if (!tokens)
	{
		printf("Tokenizer failed.\n");
		return (1);
	}

	int i = 0;
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("token[%d]: type=%d, value=[%s]\n", i, tmp->type, tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
