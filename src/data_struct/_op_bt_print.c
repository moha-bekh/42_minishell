/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 22:35:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_op_bt_print(t_pbt_op tree, bool prefix)
{
	if (!tree)
		return ;
	if (tree->root)
	{
		printf("root: ( %c ) -> tree: ( %c )\n", tree->root->operator, tree->operator);
	}
	else
	{	
		printf("tree: ( %c )\n", tree->operator);
	}
	if (prefix)
	{
		if (tree->left)
			_op_bt_print(tree->left, prefix);
		if (tree->right)
			_op_bt_print(tree->right, prefix);
	}
	else
	{
		if (tree->right)
			_op_bt_print(tree->right, prefix);
		if (tree->left)
			_op_bt_print(tree->left, prefix);
	}
	return ;
}
