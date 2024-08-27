/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:10:20 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 16:45:52 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dlst_sort(t_ppadlst dlst, bool reverse)
{
	t_pnlst	tmp;
	int		i;

	if (!*dlst)
		return ;
	i = -1;
	while (++i < (*dlst)->d_size)
	{
		tmp = (*dlst)->d_top;
		while (tmp->next)
		{
			if (ft_strcmp((char *)tmp->addr_1, (char *)tmp->next->addr_1) > 0
				&& !reverse)
			{
				ft_memswap(&tmp->addr_1, &tmp->next->addr_1, sizeof(void *));
				ft_memswap(&tmp->addr_2, &tmp->next->addr_2, sizeof(void *));
				ft_memswap(&tmp->x, &tmp->next->x, sizeof(int));
				ft_memswap(&tmp->flag, &tmp->next->flag, sizeof(bool));
			}
			tmp = tmp->next;
		}
	}
}
