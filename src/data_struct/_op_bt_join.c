/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 22:21:33 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_join(t_pbt_op tree, t_pbt_op left, t_pbt_op right)
{
	if (!tree)
		return (NULL);
	tree->left = left;
	tree->right = right;
	if (left)
		left->root = tree;
	if (right)
		right->root = tree;
	return (tree);
}
