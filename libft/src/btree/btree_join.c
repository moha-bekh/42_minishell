/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:57:00 by moha              #+#    #+#             */
/*   Updated: 2024/07/17 15:01:49 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_join(t_btree *left, t_btree *right, void *value)
{
	t_btree	*btree;

	btree = btree_create(value);
	btree->left = left;
	btree->right = right;
	if (left)
		left->parent = btree;
	if (right)
		right->parent = btree;
	return (btree);
}

// void join_res(t_btree **btree);
// join_res(&btree); // REMOVE
// void join_res(t_btree **btree)
// {
// 	ft_printf("=====================================\n"); // REMOVE
// 	ft_printf("JOIN btree ptr : %p\n", btree); // REMOVE
// 	ft_printf("WITH value : %d\n", *(int *)(*btree)->value); // REMOVE
// 	ft_printf("WITH left : %p\n", (*btree)->left); // REMOVE
// 	ft_printf("WITH value : %d\n", *(int *)(*btree)->left->value); // REMOVE
// 	ft_printf("WITH right : %p\n", (*btree)->right); // REMOVE
// 	ft_printf("WITH value : %d\n", *(int *)(*btree)->right->value); // REMOVE
// 	return ;
// }
