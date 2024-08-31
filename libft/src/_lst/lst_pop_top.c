/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop_top.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:26:10 by mbekheir          #+#    #+#             */
/*   Updated: 2024/04/29 18:30:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_pop_top(t_list **lst)
{
	t_list	*tmp;

	if (!*lst)
		return ;
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return ;
}
