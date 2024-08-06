/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:22:35 by moha              #+#    #+#             */
/*   Updated: 2024/07/18 22:57:03 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_tok_bt_print(t_pbt_tok tree, bool prefix)
{
	if (!tree)
		return ;
	if (tree->root)
		printf("root: ( %c ) -> tree: ( %c )\n", tree->root->type, tree->type);
	else
		printf("tree: ( %c )\n", tree->type);
	if (prefix)
	{
		if (tree->left)
			_tok_bt_print(tree->left, prefix);
		if (tree->right)
			_tok_bt_print(tree->right, prefix);
	}
	else
	{
		if (tree->right)
			_tok_bt_print(tree->right, prefix);
		if (tree->left)
			_tok_bt_print(tree->left, prefix);
	}
	return ;
}
