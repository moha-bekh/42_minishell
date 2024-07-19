/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:30:06 by ajordan-          #+#    #+#             */
/*   Updated: 2024/05/09 20:18:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	DESCRIPTION
 *	Takes as a parameter an element and frees the memory of the element’s
 *	content using the function ’del’ given as a parameter and free the element.
 *	The memory of ’next’ must not be freed.
 *	PARAMETERS
 *	#1. The element to free.
 *	#2. The address of the function used to delete the content.
 *	RETURN VALUES
 *	-
 */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->value);
		m_free(lst);
	}
	return ;
}
