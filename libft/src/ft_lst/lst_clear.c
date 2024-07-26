/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:37:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 16:33:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_clear(t_list *lst)
{
	t_list	*tmp;

	if (lst)
	{
		while (lst)
		{
			tmp = lst->next;
			ft_free(lst);
			lst = tmp;
		}
	}
	return ;
}
