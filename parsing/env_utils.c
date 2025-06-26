/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:26:43 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:26:50 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_env_value(char *key, char **envp)
{
    int i;
    int len;

    if (!key || !envp)
        return (NULL);
    i = 0;
    len = 0;
    while (key[len] && (key[len] != '=')) // safer to stop at '='
        len++;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            return (&envp[i][len + 1]);
        i++;
    }
    return (NULL);
}