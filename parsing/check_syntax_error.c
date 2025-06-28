/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:44 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/28 17:12:09 by haitaabe         ###   ########.fr       */
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

<<<<<<< HEAD
    if (!ft_strcmp(tokens[0], "|"))
    {
        print_error2("bash: syntax error near unexpected token","`|`");
        return (1);
=======
    if (ft_strcmp(tokens[0], "|") == 0)
    {
        printf("syntax error near unexpected token `|'\n");
        return 1;
>>>>>>> 07b2985803596596957db4592626fe53b0980a5b
    }

    while (tokens[i])
    {
<<<<<<< HEAD
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
=======
        if (ft_strcmp(tokens[i], "|") == 0 &&
            (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0))
        {
            printf("syntax error near unexpected token `|'\n");
            return 1;
        }
        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 ||
             ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0))
        {
            if (!tokens[i + 1])
            {
                printf("syntax error near unexpected token `newline'\n");
                return 1;
            }
            if (is_special(tokens[i + 1][0]))
            {
                printf("syntax error near unexpected token `%s'\n", tokens[i + 1]);
                return 1;
            }
        }
        i++;
    }

    return 0;
}
>>>>>>> 07b2985803596596957db4592626fe53b0980a5b
