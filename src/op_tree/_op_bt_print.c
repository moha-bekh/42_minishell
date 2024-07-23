/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/23 14:53:43 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_op_bt_print(t_pbt_op tree, bool prefix, int i)
{
	t_ptok tmp;
	int tab;

	tab = 0;
	if (!tree)
		return ;
	if (tree->root)
	{
		tmp = tree->token;
		while (tab++ < i)
			printf("\t");
		// printf("root: ( %s ) -> ", tree->root->token->value);
		if (tmp->type == _AND || tmp->type == _OR)
			printf(" ( %s )", tmp->value);
		while (tmp && !_tok_is(_TREE_SEP, tmp->type))
		{
			printf(" %s", tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
	{
		while (tab++ < i)
			printf("\t");
		printf("root: ( %s )\n", tree->token->value);
	}
	if (prefix)
	{
		if (tree->left)
			_op_bt_print(tree->left, prefix, i + 1);
		if (tree->right)
			_op_bt_print(tree->right, prefix, i + 1);
	}
	else
	{
		if (tree->right)
			_op_bt_print(tree->right, prefix, i + 1);
		if (tree->left)
			_op_bt_print(tree->left, prefix, i + 1);
	}
	return ;
}
	// echo 1 || (echo 2 && echo 3)
	// echo 1 || (echo 2 || ( echo 3 && echo 4) && echo 5 ) && echo 6

	// if (tree->root)
	// {
	// 	printf("root: ( %c ) -> tree: ( %c ) value: %s\n", tree->root->type, tree->type, tree->token->value);
	// }
	// else
	// {	
	// 	printf("root: ( %c ) value: %s\n", tree->type, tree->token->value);
	// }