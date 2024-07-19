/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:51:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/08 20:00:58 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_tab(int tab)
{
	while (tab > 0)
	{
		ft_printf("\t");
		tab--;
	}
}

void	print_parent(t_btree *btree)
{
	if (btree->parent)
		ft_printf("[%d] -> [%d]\n", *(int *)btree->parent->value,
			*(int *)btree->value);
	else
		ft_printf("[%d]\n", *(int *)btree->value);
}
