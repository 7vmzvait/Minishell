/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    token.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:45:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:32 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *new_token(t_token_type type, char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->type = type;
    token->value = value;
    token->next = NULL;
    return token;
}

void add_token(t_token **head, t_token *new_token)
{
    t_token *tmp;

    if (!head || !new_token)
        return;
    if (!*head)
        *head = new_token;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
}

void free_token_list(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}
