/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:24:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/12 11:32:03 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char *trim_and_squash_whitespace(const char *str)
{
    char *res = malloc(ft_strlen(str) + 1);
    int i = 0, j = 0;
    int in_space = 0;

    if (!res)
        return NULL;

    while (str[i])
    {
        if (is_space(str[i]))
        {
            if (!in_space && j > 0)
                res[j++] = ' ';
            in_space = 1;
        }
        else
        {
            res[j++] = str[i];
            in_space = 0;
        }
        i++;
    }
    res[j] = '\0';
    return res;
}

char *getenv_from_envp(char *var, char **envp)
{
    int i = 0;
    int len = ft_strlen(var);

    while (envp[i])
    {
        if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
            return &envp[i][len + 1];
        i++;
    }
    return NULL;
}

char *expand_variables(const char *input, char **envp, int exit_status, int split)
{
    char *result = ft_strdup("");
    int i = 0;

    while (input[i])
    {
        if (input[i] == '$')
        {
            i++;
            if (input[i] == '?')
            {
                char *exit_code = ft_itoa_custom(exit_status);
                result = strjoin_and_free(result, exit_code);
                free(exit_code);
                i++;
            }
            else if (is_valid_var_char(input[i]))
            {
                int start = i;
                while (is_valid_var_char(input[i]))
                    i++;
                char *var_name = ft_substr(input, start, i - start);
                char *value = getenv_from_envp(var_name, envp);
                if (value)
                {
                    char *to_add = split ? trim_and_squash_whitespace(value) : ft_strdup(value);
                    result = strjoin_and_free(result, to_add);
                    free(to_add);
                }
                free(var_name);
            }
            else
            {
                result = strjoin_and_free_char(result, '$');
                result = strjoin_and_free_char(result, input[i]);
                i++;
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
