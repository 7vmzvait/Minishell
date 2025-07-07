/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:24:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:22:59 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char *get_env_value(char *key, char **envp)
{
    int i = 0;
    int len_key = ft_strlen(key);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, len_key) == 0 && envp[i][len_key] == '=')
            return (&envp[i][len_key + 1]);
        i++;
    }
    return NULL;
}

char *extract_var_name(const char *str, int *i)
{
    int start = *i;
    int len = 0;

    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
    {
        (*i)++;
        len++;
    }

    return ft_substr(str, start, len);
}


char *expand_variables(const char *input, char **envp, int exit_status)
{
    char *result = ft_strdup("");
    int i = 0;
    char *var_name, *var_value, *exit_str;
    int in_single = 0, in_double = 0;

    if (!result)
        return NULL;

    while (input[i])
    {
        if (input[i] == '\'' && !in_double)
        {
            in_single = !in_single;
            result = strjoin_and_free_char(result, input[i++]);
        }
        else if (input[i] == '\"' && !in_single)
        {
            in_double = !in_double;
            result = strjoin_and_free_char(result, input[i++]);
        }
        else if (input[i] == '$' && !in_single)
        {
            i++;
            if (input[i] == '?')
            {
                exit_str = ft_itoa_custom(exit_status);
                result = strjoin_and_free(result, exit_str);
                free(exit_str);
                i++;
            }
            else if (input[i] && (ft_isalpha(input[i]) || input[i] == '_'))
            {
                var_name = extract_var_name(input, &i);
                var_value = get_env_value(var_name, envp);
                result = strjoin_and_free(result, var_value ? var_value : "");
                free(var_name);
            }
            else
            {
                result = strjoin_and_free_char(result, '$');
                if (input[i])
                    result = strjoin_and_free_char(result, input[i++]);
            }
        }
        else
        {
            result = strjoin_and_free_char(result, input[i++]);
        }
    }

    return result;
}
