/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:10:53 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:35 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_itoa_custom(int n)
{
	unsigned int	num;
    int i = 10;
    int neg = n < 0;

	// Simple implementation of itoa
	char buffer[12]; // enough for int range
	i = 10;
	neg = n < 0;
	buffer[11] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	num = (neg) ? -n : n;
	while (num > 0)
	{
		buffer[i--] = '0' + (num % 10);
		num /= 10;
	}
	if (neg)
		buffer[i--] = '-';
	return (ft_strdup(&buffer[i + 1]));
}
