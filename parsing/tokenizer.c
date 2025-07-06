/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/06 09:50:12 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../include/minishell.h"

static int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

char **tokenize(char *line, t_env *env)
{
    char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
    if (!tokens)
        return NULL;

    char **env_path = list_to_array(env, NULL);
    int i = 0, j = 0;

    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;

        // Collect segments (quoted or unquoted) as one token like bash
        char token_buf[4096] = {0};
        int has_token = 0;

        while (line[i] && !is_space(line[i]) && !is_special_char(line[i]))
        {
            if (line[i] == '"' || line[i] == '\'')
            {
                int is_single = 0;
                char *word = extract_quoted(line, &i, &is_single);
                if (!word)
                {
                    print_error2("bash: syntax error near unexpected token", "`newline'");
                    free_tokens(tokens);
                    return NULL;
                }
                char *expanded;
                if (is_single)
                    expanded = strdup(word); // No expansion in single quotes
                else
                    expanded = expand_variables(word, env_path, 0); // Expand in double quotes
                strcat(token_buf, expanded);
                free(word);
                free(expanded);
                has_token = 1;
            }
            else
            {
                int start = i;
                while (line[i] && !is_space(line[i]) && !is_special_char(line[i]) && line[i] != '"' && line[i] != '\'')
                    i++;
                if (i > start)
                {
                    char *word = ft_substr(line, start, i - start);
                    char *expanded = expand_variables(word, env_path, 0);
                    strcat(token_buf, expanded);
                    free(word);
                    free(expanded);
                    has_token = 1;
                }
            }
        }
        if (has_token)
            tokens[j++] = strdup(token_buf);

        // Special character tokens
        if (line[i] && is_special_char(line[i]))
        {
            int len = 1;
            if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
                len = 2;
            tokens[j++] = ft_substr(line, i, len);
            i += len;
        }
    }
    tokens[j] = NULL;
    // free env_path if needed here
    return tokens;
}