/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:44 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:50 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error2(const char *prefix, const char *name)
{
	write(2, "minishell: ", 11);
	if (prefix)
	{
		write(2, prefix, strlen(prefix));
		write(2, ": ", 2);
	}
	if (name)
	{
		write(2, name, strlen(name));
		write(2, "\n", 2);
	}
}

int check_syntax_error(char **tokens)
{
    int i = 0;

    if (!tokens || !tokens[0])
        return 1;

    if (!ft_strcmp(tokens[0], "|"))
    {
        print_error2("bash: syntax error near unexpected token","`|`");
        return (1);
    }

    while (tokens[i])
    {
        // if (!ft_strcmp(tokens[i], "|") && (!tokens[i + 1] || !ft_strcmp(tokens[i + 1], "|")))
        if (!ft_strcmp(tokens[i], "|") && tokens[i + 1] && !ft_strcmp(tokens[i + 1], "|"))
        {
            print_error2("syntax error near unexpected token","`||'");
            return (1);
        }
        if (( !ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") ||
             !ft_strcmp(tokens[i], "<<") || !ft_strcmp(tokens[i], ">>")) &&
            (!tokens[i + 1] || is_special(tokens[i + 1][0])))
        {
            print_error2("syntax error near unexpected token","`newline'");
            return (1);
        }

        i++;
    }

    return (0); // no syntax error
}