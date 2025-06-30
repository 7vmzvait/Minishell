/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:24:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:25:54 by haitaabe         ###   ########.fr       */
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

char *expand_variables(const char *input, char **envp, int exit_status)
{
    char *result;
    int i = 0;
    int len = ft_strlen(input);
    char *var_name;
    char *var_value;
    char *exit_str;

    result = ft_strdup(""); // start with empty string
    if (!result)
        return NULL;

    while (i < len)
    {
        if (input[i] == '$')
        {
            i++;
            if (input[i] == '?')
            {
                exit_str = ft_itoa_custom(exit_status);
                result = strjoin_and_free(result, exit_str);
                free(exit_str);
                i++;
            }
            else if (is_valid_var_char(input[i]))
            {
                // extract variable name starting at input[i]
                var_name = extract_var_name(input, &i);
                var_value = get_env_value(var_name, envp);
                if (!var_value)
                    var_value = ""; // no value found -> empty
                result = strjoin_and_free(result, var_value);
                free(var_name);
            }
            else
            {
                // $ followed by non-valid var char, just add '$' + char
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