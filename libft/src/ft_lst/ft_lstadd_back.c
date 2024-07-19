/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:04:23 by ajordan-          #+#    #+#             */
/*   Updated: 2024/05/01 20:00:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	DESCRIPTION
 *	Adds the element ’new’ at the end of the list.
 *	PARAMETERS
 *	#1. The address of a pointer to the first link of a list.
 *	#2. The address of a pointer to the element to be added to the list.
 *	RETURN VALUES
 *	-
 */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		if (*lst)
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
		else
			*lst = new;
	}
	return ;
}
