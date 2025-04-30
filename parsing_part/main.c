/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:46:45 by haitaabe          #+#    #+#             */
/*   Updated: 2025/04/30 16:33:41 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main()
{
    char *line = NULL;
    while ((line = readline("Minishell ~: ")))
    {
        add_history(line);
        printf("%s\n", line);
        free(line);
    }
    printf("exit\n");
}