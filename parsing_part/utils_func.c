/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:55:09 by haitaabe          #+#    #+#             */
/*   Updated: 2025/04/30 14:58:43 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int chexk_is_space(int check)
{
    return (check == 32 || (check >= 9 && check <= 13));
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
    {
        i++;
    }
    return (s1[i] - s2[i]);   
}