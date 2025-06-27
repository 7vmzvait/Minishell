/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:31:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:36:43 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
void print1(t_cmd *cmd)
{
    int i;
    while (cmd)
    {
        printf("Command: ");
        for (i = 0; cmd->args && cmd->args[i]; i++)
            printf("[%s] ", cmd->args[i]);
        printf("\n");
        cmd = cmd->next;
    }
}
t_cmd *parse_input(char *input)
{
    char **tokens;
    t_cmd *cmds;

    tokens = tokenize(input);

    if (!tokens)
        return (NULL);
    if (check_syntax_error(tokens))
    {
        free_tokens(tokens);
        return (NULL);
    }
    cmds = parse_tokens1(tokens);
    print1(cmds);
    //free_tokens(tokens);
    return (cmds);
}

char **tokenize(char *line)
{
    int i;
    int j;
    char **tokens;
    char *word;
    char *expanded;

    tokens = malloc(sizeof(char *) * (MAX_TOKENS));
    if (!tokens)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        while (line[i] && is_space(line[i]))
            i++;
        if (!line[i])
            break;
        // if (is_special(line[i]))
        // {
        //     tokens[j++] = get_special_token(line, &i);
        // }
        else if (line[i] == '"' || line[i] == '\'')
        {
            word = extract_quoted(line, &i);
            expanded = expand_variables(word, NULL, 0); // Pass envp & exit_status here
            free(word);
            tokens[j++] = expanded;
        }
        else
        {
            word = extract_word(line, &i);
            expanded = expand_variables(word, NULL, 0); // Pass envp & exit_status here
            free(word);
            tokens[j++] = expanded;
        }
    }
    tokens[j] = NULL;
    return (tokens);
}