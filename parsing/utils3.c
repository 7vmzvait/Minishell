/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:27:01 by haitaabe          #+#    #+#             */
/*   Updated: 2025/05/30 13:28:29 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Add token to the end of the list
void add_token(t_token **head, int type, char *value)
{
    t_token *new = malloc(sizeof(t_token));
    if (!new)
        return;

    new->type = type;
    new->value = ft_strdup(value);
    new->next = NULL;

    if (!*head)
        *head = new;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}