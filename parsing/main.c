/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:15:32 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/17 20:15:47 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
int main() {
    char *line = "ls -l | grep txt > output.txt";
    char **tokens = tokenize_input(line);

    for (int i = 0; tokens[i]; i++)
        printf("token[%d]: %s\n", i, tokens[i]);

    // Don’t forget to free tokens later
}
