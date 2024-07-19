/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:51:36 by moha              #+#    #+#             */
/*   Updated: 2024/05/01 19:58:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_clear(t_btree *btree)
{
	if (!btree)
		return ;
	btree_clear(btree->left);
	btree_clear(btree->right);
	free(btree);
	return ;
}

// void	clear_res(t_btree **btree);
// clear_res(&btree); // REMOVE
// void	clear_res(t_btree **btree)
// {
// 	ft_printf("=====================================\n");    // REMOVE
// 	ft_printf("CLEAR btree ptr : %p\n", btree);              // REMOVE
// 	ft_printf("WITH value : %d\n", *(int *)(*btree)->value); // REMOVE
// 	return ;
// }
