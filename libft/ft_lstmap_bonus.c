/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:54:34 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/09 11:47:59 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*fnew;

	cpy = NULL;
	fnew = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		fnew = ft_lstnew(f(lst->content));
		if (!fnew)
		{
			ft_lstclear(&fnew, del);
			return (NULL);
		}
		ft_lstadd_back(&cpy, fnew);
		lst = lst->next;
	}
	return (cpy);
}
