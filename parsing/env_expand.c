/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:24:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 21:18:07 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char *get_env_value(char *key, char **envp)
{
    int i;
    int len_key;

    i = 0;
    len_key = ft_strlen(key);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, len_key) == 0 && envp[i][len_key] == '=')
            return (&envp[i][len_key + 1]);
        i++;
    }
    return (NULL);
}

#include "parsing.h"

char *expand_variables(const char *input, char **envp, int exit_status, int in_single_quotes)
{
    if (in_single_quotes)
        return ft_strdup(input);  // Skip expansion if in single quotes

    char *result = ft_strdup("");
    int i = 0;

    while (input[i])
    {
        if (input[i] == '$')
        {
            i++;
            if (input[i] == '?')  // handle $?
            {
                char *exit_str = ft_itoa_custom(exit_status);
                result = strjoin_and_free(result, exit_str);
                i++;
            }
            else if (ft_isalpha(input[i]) || input[i] == '_')
            {
                int start = i;
                while (ft_isalnum(input[i]) || input[i] == '_')
                    i++;

                char *key = ft_substr(input, start, i - start);
                char *value = get_env_value(key, envp);
                result = strjoin_and_free(result, value ? value : "");
                free(key);
            }
            else
            {
                result = strjoin_and_free_char(result, '$');
            }
        }
        else
        {
            result = strjoin_and_free_char(result, input[i]);
            i++;
        }
    }
    return result;
}
