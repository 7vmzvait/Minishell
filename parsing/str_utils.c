/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:27:37 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:27:44 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *strjoin_and_free(char *s1, const char *s2)
{
    char *new_str;
    int len1;
    int len2;
    int i;
    int j;

    if (!s1 && !s2)
        return (NULL);
    len1 = 0;
    len2 = 0;
    while (s1 && s1[len1])
        len1++;
    while (s2 && s2[len2])
        len2++;
    new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (s1 && s1[i])
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 && s2[j])
        new_str[i++] = s2[j++];
    new_str[i] = '\0';
    if (s1)
        free(s1);
    return (new_str);
}

char *strjoin_and_free_char(char *s, char c)
{
    char *new_str;
    int len;
    int i;

    len = 0;
    while (s && s[len])
        len++;
    new_str = malloc(len + 2);
    if (!new_str)
        return (NULL);
    i = 0;
    while (s && s[i])
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i++] = c;
    new_str[i] = '\0';
    if (s)
        free(s);
    return (new_str);
}