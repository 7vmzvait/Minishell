/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 21:47:51 by haitaabe         ###   ########.fr       */
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
    int is_single_quote;

    tokens = malloc(sizeof(char *) * MAX_TOKENS);
    if (!tokens)
        return (NULL);

    extern char **__environ;

    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;

        if (line[i] == '"' || line[i] == '\'')
        {
            is_single_quote = 0;
            word = extract_quoted(line, &i, &is_single_quote);  // ✅ now passes 3 args
            if (!is_single_quote)
                expanded = expand_variables(word, __environ, 0, 0);  // ✅ not in single quotes
            else
                expanded = ft_strdup(word); // ✅ don't expand in single quotes
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
            word = extract_word(line, &i);  // normal word
            expanded = expand_variables(word, __environ, 0, 0); // ✅ assume outside quotes
            free(word);
            tokens[j++] = expanded;
        }
    }
    tokens[j] = NULL;
    return tokens;
}
