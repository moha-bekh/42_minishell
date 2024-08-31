/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last_prev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:04:55 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/01 20:00:40 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lst_last_prev(t_list *lst)
{
	t_list	*tmp;

	if (!lst || !lst->next)
		return (NULL);
	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}
