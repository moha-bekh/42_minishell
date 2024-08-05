/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 22:09:52 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_op_bt_print(t_pbt_op tree, bool prefix, int i)
{
	t_ptok	tmp;
	int		tab;

	tab = 0;
	if (!tree)
		return ;
	if (tree->root)
	{
		tmp = tree->token;
		while (tab++ < i)
			printf("\t");
		if (tmp->type == _AND || tmp->type == _OR)
			printf(" ( %s )", tmp->value);
		// printf("\ttokens: ");
		// while (tmp && !_tok_is(_TYPE_SEP, tmp->type))
		// {
		// 	printf(" %s", tmp->value);
		// 	tmp = tmp->next;
		// }
		_cmd_print(tree->cmd);
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