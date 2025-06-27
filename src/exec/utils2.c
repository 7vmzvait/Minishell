/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:08:08 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:05:26 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **split_path)
{
	int	i;

	i = 0;
	if (!split_path)
		return ;
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
}

