/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:21:58 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:35:12 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pbt_tok	_tok_bt_join(t_pbt_tok tree, t_pbt_tok left, t_pbt_tok right)
{
	tree->left = left;
	tree->right = right;
	if (left)
		left->root = tree;
	if (right)
		right->root = tree;
	return (tree);
}
