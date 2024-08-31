/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:02:13 by ajordan-          #+#    #+#             */
/*   Updated: 2024/05/01 20:00:30 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	DESCRIPTION
 *	Returns the last element of the list.
 *	PARAMETERS
 *	#1. The beginning of the list.
 *	RETURN VALUES
 *	Last element of the list.
 */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
