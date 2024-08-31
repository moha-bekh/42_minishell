/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:03:37 by ajordan-          #+#    #+#             */
/*   Updated: 2024/05/01 20:00:34 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*obj;

	if (lst && f)
	{
		new = NULL;
		obj = NULL;
		while (lst)
		{
			obj = ft_lstnew(f(lst->value));
			if (!obj)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, obj);
			lst = lst->next;
		}
		return (new);
	}
	return (NULL);
}
