/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:21:18 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

char **tokenize(char *line)
{
    char **tokens;
    int i = 0;
    int j = 0;
    char *word;
    char *expanded;

    tokens = malloc(sizeof(char *) * MAX_TOKENS);
    if (!tokens)
        return (NULL);

    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;
        
        if (line[i] == '"' || line[i] == '\'')
        {
            word = extract_quoted(line, &i);
            expanded = expand_variables(word, NULL, 0); // add envp and exit_status if needed
            free(word);
            tokens[j++] = expanded;
        }
        else if (is_special_char(line[i]))
        {
            int len = 1;
            if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
                len = 2;

            tokens[j++] = ft_substr(line, i, len);
            i += len;
        }
        else
        {
            word = extract_word(line, &i);
            expanded = expand_variables(word, NULL, 0); // handle env later
            free(word);
            tokens[j++] = expanded;
        }
    }
    tokens[j] = NULL;
    return tokens;
}
