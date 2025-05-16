/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:08:34 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/21 16:00:36 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	res;

	sign = 1;
	index = 0;
	res = 0;
	while (*str == 32 || *str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == '\n')
	{
		str++;
	}
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = res * 10 + (str[index] - '0');
		index++;
	}
	return (res * sign);
}
