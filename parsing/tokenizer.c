/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/29 19:13:03 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void free_all(char **tokens)
{
    int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}

char **tokenize(char *line)
{
    char **tokens;
    int i = 0;
    int j = 0;
    int is_single_quote;
    char *fragment;
    char *word;
    char *tmp;

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

        word = ft_strdup("");
        if (!word)
            return (free_all(tokens), NULL);

        while (line[i] && !is_space(line[i]) && !is_special_char(line[i]))
        {
            if (line[i] == '\'' || line[i] == '\"')
            {
                is_single_quote = (line[i] == '\'');
                fragment = extract_quoted(line, &i, &is_single_quote);
                if (!fragment)
                {
                    printf("syntax error: unclosed quote\n");
                    free(word);
                    free_all(tokens);
                    return NULL;
                }

                if (!is_single_quote)
                    tmp = expand_variables(fragment, __environ, 0, 0);
                else
                    tmp = ft_strdup(fragment);
                free(fragment);
            }
            else
            {
                fragment = extract_word(line, &i);
                if (!fragment)
                {
                    free(word);
                    free_all(tokens);
                    return NULL;
                }
                tmp = expand_variables(fragment, __environ, 0, 0);
                free(fragment);
                fragment = extract_quoted(line, &i, &is_single_quote);
                if (!fragment)
                {
                    printf("syntax error: unclosed quote\n");
                    free(word);
                    free_all(tokens);
                    return NULL;
                }
            }

            if (!tmp)
            {
                free(word);
                free_all(tokens);
                return NULL;
            }

            char *joined = ft_strjoin(word, tmp);
            free(word);
            free(tmp);
            if (!joined)
            {
                free_all(tokens);
                return NULL;
            }
            word = joined;
        }

        if (word && *word)
            tokens[j++] = word;
        else
            free(word);

        if (is_special_char(line[i]))
        {
            int len = 1;
            if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
                len = 2;
            tokens[j++] = ft_substr(line, i, len);
            i += len;
        }
    }

    tokens[j] = NULL;
    return tokens;
}
