/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_bt_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:39:16 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:42:20 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pbt_blc	_blc_bt_join(t_pbt_blc tree, t_pbt_blc left, t_pbt_blc right)
{
	tree->left = left;
	tree->right = right;
	if (left)
		left->root = tree;
	if (right)
		right->root = tree;
	return (tree);
}
